#include "MagazzinoFrame.h"
#include <wx/msgdlg.h>
#include <wx/dataview.h>
#include <wx/filedlg.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Costanti ID per la comunicazione tra thread
enum {
    ID_REFRESH_NET_EVENT = 9999
};

// ============================================================================
// FUNZIONI HELPER: SERIALIZZAZIONE & DESERIALIZZAZIONE JSON (Dependency-Free)
// ============================================================================
string MagazzinoToJSON(Magazzino* m) {
    string json = "[\n";
    for (int i = 0; i < m->contap; i++) {
        json += "  {\n";
        json += "    \"nome\": \"" + m->p[i].nome + "\",\n";
        json += "    \"prezzo\": " + to_string(m->p[i].prezzo) + ",\n";
        json += "    \"quantita\": " + to_string(m->p[i].quantita) + "\n";
        json += "  }";
        if (i < m->contap - 1) json += ",";
        json += "\n";
    }
    json += "]";
    return json;
}

bool JSONToMagazzino(Magazzino* m, const string& jsonStr) {
    m->contap = 0;
    stringstream ss(jsonStr);
    string line;
    string nome = "";
    double prezzo = 0.0;
    int quantita = 0;
    bool haNome = false, haPrezzo = false, haQuantita = false;

    while (getline(ss, line)) {
        if (line.find("\"nome\":") != string::npos) {
            size_t start = line.find("\"", line.find("\"nome\":") + 7);
            size_t end = line.find("\"", start + 1);
            if (start != string::npos && end != string::npos) {
                nome = line.substr(start + 1, end - start - 1);
                haNome = true;
            }
        }
        else if (line.find("\"prezzo\":") != string::npos) {
            size_t start = line.find("\"prezzo\":") + 9;
            size_t end = line.find_first_of(",\n\r", start);
            prezzo = stod(line.substr(start, end - start));
            haPrezzo = true;
        }
        else if (line.find("\"quantita\":") != string::npos) {
            size_t start = line.find("\"quantita\":") + 11;
            size_t end = line.find_first_of(",\n\r", start);
            quantita = stoi(line.substr(start, end - start));
            haQuantita = true;
        }

        if (haNome && haPrezzo && haQuantita) {
            if (m->contap < 100) {
                m->p[m->contap] = { nome, prezzo, quantita };
                m->contap++;
            }
            haNome = haPrezzo = haQuantita = false;
        }
    }
    return true;
}

// ============================================================================
// FUNZIONE THREAD: SERVER DI ASCOLTO BACKGROUND
// ============================================================================
void ServerWorker(MagazzinoMainFrame* mainFrame, Magazzino* m, int porto, std::atomic<bool>* running) {
    wxIPV4address addr;
    addr.AnyAddress();
    addr.Service(porto);

    // Socket bloccante all'interno del thread dedicato
    wxSocketServer* server = new wxSocketServer(addr, wxSOCKET_BLOCK);
    if (!server->IsOk()) {
        server->Destroy();
        return;
    }

    while (running->load()) {
        // Attende una connessione (timeout breve per non bloccare il loop di chiusura)
        wxSocketBase* client = server->Accept(false); 
        if (!client) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        string jsonRicevuto = "";
        char buffer[1024];
        
        while (true) {
            client->Read(buffer, sizeof(buffer) - 1);
            size_t letti = client->LastCount();
            if (letti == 0) break;
            buffer[letti] = '\0';
            jsonRicevuto += buffer;
        }
        client->Destroy();

        if (!jsonRicevuto.empty()) {
            JSONToMagazzino(m, jsonRicevuto);

            // Spedisce un evento sicuro al thread principale della UI per aggiornare la grafica
            wxCommandEvent* evt = new wxCommandEvent(wxEVT_COMMAND_TEXT_UPDATED, ID_REFRESH_NET_EVENT);
            wxQueueEvent(mainFrame, evt);
        }
    }
    server->Destroy();
}

// ==========================================
// 1. FINESTRA AGGIUNGI PRODOTTO
// ==========================================
class MagazzinoUIAdd : public m_FrameAddProduct {
private:
    Magazzino* m_reale;

public:
    MagazzinoUIAdd(wxWindow* parent, Magazzino* istanzaDati) : m_FrameAddProduct(parent) {
        m_reale = istanzaDati;
    }

    void AggiungiProdotto(wxCommandEvent& event) override {
        if (m_reale->contap >= 100) {
            wxMessageBox("Magazzino pieno!", "Errore", wxOK | wxICON_ERROR, this);
            return;
        }

        wxString nomeWx = m_txtnomeadd->GetValue();
        nomeWx.Trim(true).Trim(false);
        string nuovoNome = nomeWx.ToStdString();

        if (nuovoNome.empty()) {
            wxMessageBox("Errore: Il nome del prodotto non può essere vuoto!", "Errore Input", wxOK | wxICON_WARNING, this);
            return;
        }

        for (int i = 0; i < m_reale->contap; i++) {
            wxString nomeEsistente(m_reale->p[i].nome);
            if (nomeEsistente.CmpNoCase(nomeWx) == 0) {
                wxMessageBox("Errore: Un prodotto con questo nome è già presente nel magazzino!", "Prodotto Duplicato", wxOK | wxICON_WARNING, this);
                return;
            }
        }

        string prezzoStr = m_txtprezzoadd->GetValue().ToStdString();
        try {
            m_reale->p[m_reale->contap].prezzo = stod(prezzoStr);
        } catch (...) {
            wxMessageBox("Errore: Il prezzo inserito non è valido!", "Errore Input", wxOK | wxICON_ERROR, this);
            return;
        }

        string quantitaStr = m_txtquantitaadd->GetValue().ToStdString();
        try {
            m_reale->p[m_reale->contap].quantita = stoi(quantitaStr);
        } catch (...) {
            wxMessageBox("Errore: La quantità inserita non è valida!", "Errore Input", wxOK | wxICON_ERROR, this);
            return;
        }

        m_reale->p[m_reale->contap].nome = nuovoNome;
        m_reale->contap += 1;

        // Notifica la rete e aggiorna le UI locali/remote
        MagazzinoMainFrame* master = dynamic_cast<MagazzinoMainFrame*>(GetParent());
        if (master) {
            master->InviaAggiornamentoNetwork();
            master->ForzaAggiornamentoUI();
        }

        wxMessageBox("Prodotto aggiunto con successo!", "Successo", wxOK | wxICON_INFORMATION, this);
        this->Close();
    }
};

// ==========================================
// 2. FINESTRA RIMUOVI PRODOTTO
// ==========================================
class MagazzinoUIRemove : public m_FrameRemoveProduct {
private:
    Magazzino* m_reale;

public:
    MagazzinoUIRemove(wxWindow* parent, Magazzino* istanzaDati) : m_FrameRemoveProduct(parent) {
        m_reale = istanzaDati;
    }

    void RemoveProduct(wxCommandEvent& event) override {
        string daRimuovere = m_txtctrl2remove->GetValue().ToStdString();
        int indiceTrovato = -1;

        for (int i = 0; i < m_reale->contap; i++) {
            if (m_reale->p[i].nome == daRimuovere) {
                indiceTrovato = i;
                break;
            }
        }

        if (indiceTrovato == -1) {
            m_RemovedProduct->SetLabel("Prodotto non trovato nel magazzino!");
            return;
        }

        for (int i = indiceTrovato; i < m_reale->contap - 1; i++) {
            m_reale->p[i] = m_reale->p[i + 1];
        }

        m_reale->contap -= 1;

        // Notifica rete e aggiorna UI
        MagazzinoMainFrame* master = dynamic_cast<MagazzinoMainFrame*>(GetParent());
        if (master) {
            master->InviaAggiornamentoNetwork();
            master->ForzaAggiornamentoUI();
        }

        wxMessageBox("Prodotto rimosso con successo!", "Successo", wxOK | wxICON_INFORMATION, this);
        this->Close();
    }
};

// ==========================================
// 3. FINESTRA MOSTRA PRODOTTI (Dinamica)
// ==========================================
class MagazzinoUIList : public m_FrameProductList {
private:
    wxDataViewListStore* m_store;
public:
    MagazzinoUIList(wxWindow* parent, Magazzino* istanzaDati) : m_FrameProductList(parent) {
        m_store = new wxDataViewListStore();
        m_dataViewCtrl5->ClearColumns();
        m_dataViewCtrl5->AssociateModel(m_store);
        m_store->DecRef();

        m_dataViewCtrl5->AppendTextColumn("Prodotto",  0, wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT);
        m_dataViewCtrl5->AppendTextColumn("Prezzo",    1, wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT);
        m_dataViewCtrl5->AppendTextColumn(wxT("Quantità"), 2, wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT);

        RicaricaTabella(istanzaDati);
    }

    void RicaricaTabella(Magazzino* istanzaDati) {
        m_store->DeleteAllItems();
        for (int i = 0; i < istanzaDati->contap; i++) {
            wxVector<wxVariant> data;
            data.push_back(wxVariant(istanzaDati->p[i].nome));
            data.push_back(wxVariant(wxString::Format(wxT("%.2f €"), istanzaDati->p[i].prezzo)));
            data.push_back(wxVariant(wxString::Format(wxT("%d"),     istanzaDati->p[i].quantita)));
            m_store->AppendItem(data);
        }
    }
};

// ==========================================
// 4. PROCEDURA GUIDATA MODIFICA (WIZARD)
// ==========================================
class MagazzinoUIWizard : public m_WizardModify {
private:
    Magazzino* m_reale;
    int m_indiceTrovato;

public:
    MagazzinoUIWizard(wxWindow* parent, Magazzino* istanzaDati) : m_WizardModify(parent) {
        m_reale = istanzaDati;
        m_indiceTrovato = -1;
        this->Bind(wxEVT_WIZARD_PAGE_CHANGING, &MagazzinoUIWizard::OnPageChanging, this);
    }

    void OnPageChanging(wxWizardEvent& event) {
        if (event.GetDirection() && event.GetPage() == m_pages.Item(0)) {
            string nomeDaCercare = m_TxtCtrlProduct2modify->GetValue().ToStdString();
            m_indiceTrovato = -1;

            for (int i = 0; i < m_reale->contap; i++) {
                if (m_reale->p[i].nome == nomeDaCercare) {
                    m_indiceTrovato = i;
                    break;
                }
            }

            if (m_indiceTrovato == -1) {
                m_ProdottoNonTrovato->SetLabel("Errore: Il prodotto inserito non esiste!");
                m_ProdottoNonTrovato->SetForegroundColour(*wxRED);
                this->Layout();
                event.Veto();
                return;
            }

            m_ProdottoNonTrovato->SetLabel("");
            m_txtproductname2modify->SetValue(m_reale->p[m_indiceTrovato].nome);
            m_txtproductprice2modify->SetValue(wxString::Format(wxT("%.2f"), m_reale->p[m_indiceTrovato].prezzo));
            m_txtproductquantiy2modify->SetValue(wxString::Format(wxT("%d"), m_reale->p[m_indiceTrovato].quantita));
        }
    }

    void SalvaModifiche() {
        if (m_indiceTrovato != -1) {
            try {
                m_reale->p[m_indiceTrovato].nome     = m_txtproductname2modify->GetValue().ToStdString();
                m_reale->p[m_indiceTrovato].prezzo   = stod(m_txtproductprice2modify->GetValue().ToStdString());
                m_reale->p[m_indiceTrovato].quantita = stoi(m_txtproductquantiy2modify->GetValue().ToStdString());

                wxMessageBox("Prodotto modificato con successo!", "Successo", wxOK | wxICON_INFORMATION, this);
            } catch (...) {
                wxMessageBox("Errore: I dati numerici immessi non sono validi!", "Errore Modifica", wxOK | wxICON_ERROR, this);
            }
        }
    }
};

// ==========================================
// 5. FINESTRA PRINCIPALE (Logica di Core)
// ==========================================
MagazzinoMainFrame::MagazzinoMainFrame(wxWindow* parent, Magazzino* istanzaDati) : m_MainFrame(parent) {
    m_reale = istanzaDati;
    m_listaAperta = nullptr;
    m_running.store(true);

    // Sistema di rilevamento dinamico della porta per testare localmente due istanze
    wxIPV4address testAddr;
    testAddr.AnyAddress();
    testAddr.Service(5000);
    wxSocketServer* testServer = new wxSocketServer(testAddr);
    
    if (testServer->IsOk()) {
        // Porta 5000 libera -> Istanza Principale
        m_portoAscolto = 5000;
        m_portoDestinazione = 5001;
    } else {
        // Porta 5000 occupata -> Seconda Istanza di test
        m_portoAscolto = 5001;
        m_portoDestinazione = 5000;
    }
    testServer->Destroy();

    // Avvio del thread di ascolto socket in background
    m_serverThread = std::thread(ServerWorker, this, m_reale, m_portoAscolto, &m_running);

    // Bind del segnale custom cross-thread proveniente dal socket worker
    this->Bind(wxEVT_COMMAND_TEXT_UPDATED, &MagazzinoMainFrame::OnNetworkUpdateEvent, this, ID_REFRESH_NET_EVENT);
}

MagazzinoMainFrame::~MagazzinoMainFrame() {
    m_running.store(false);
    
    // Forza la chiusura del thread inviando un segnale fittizio per sbloccare Accept() se necessario
    wxIPV4address addr;
    addr.Hostname("127.0.0.1");
    addr.Service(m_portoAscolto);
    wxSocketClient* killShot = new wxSocketClient();
    killShot->Connect(addr, false);
    killShot->Destroy();

    if (m_serverThread.joinable()) {
        m_serverThread.join();
    }
}

// Spedisce la lista corrente in formato JSON all'altra istanza tramite Socket
void MagazzinoMainFrame::InviaAggiornamentoNetwork() {
    wxIPV4address addr;
    addr.Hostname("127.0.0.1");
    addr.Service(m_portoDestinazione);

    wxSocketClient* client = new wxSocketClient(wxSOCKET_BLOCK);
    // Tenta la connessione per un massimo di 500ms per non impallare l'interfaccia
    if (client->Connect(addr, false)) {
        string payload = MagazzinoToJSON(m_reale);
        client->Write(payload.c_str(), payload.length());
    }
    client->Destroy();
}

// Se la finestra con l'elenco dei prodotti è attualmente aperta, la rinfresca al volo
void MagazzinoMainFrame::ForzaAggiornamentoUI() {
    if (m_listaAperta) {
        m_listaAperta->RicaricaTabella(m_reale);
    }
}

// Intercetta l'aggiornamento arrivato dal socket di rete
void MagazzinoMainFrame::OnNetworkUpdateEvent(wxCommandEvent& event) {
    ForzaAggiornamentoUI();
}

void MagazzinoMainFrame::AddProductFrame(wxCommandEvent& event) {
    MagazzinoUIAdd* frameAdd = new MagazzinoUIAdd(this, m_reale);
    frameAdd->Show(true);
}

void MagazzinoMainFrame::ShowProductFrame(wxCommandEvent& event) {
    // Evita aperture multiple della stessa finestra controllando il puntatore di stato
    if (!m_listaAperta) {
        m_listaAperta = new MagazzinoUIList(this, m_reale);
        m_listaAperta->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& e) {
            m_listaAperta = nullptr;
            e.Skip();
        });
        m_listaAperta->Show(true);
    } else {
        m_listaAperta->Raise(); // Porta in primo piano l'elenco già aperto
    }
}

void MagazzinoMainFrame::RemoveProductFrame(wxCommandEvent& event) {
    MagazzinoUIRemove* frameRemove = new MagazzinoUIRemove(this, m_reale);
    frameRemove->Show(true);
}

void MagazzinoMainFrame::ModifyProductFrame(wxCommandEvent& event) {
    MagazzinoUIWizard* wizard = new MagazzinoUIWizard(this, m_reale);

    if (wizard->m_pages.GetCount() > 0) {
        wxWizardPage* firstPage = dynamic_cast<wxWizardPage*>(wizard->m_pages.Item(0));
        if (wizard->RunWizard(firstPage)) {
            wizard->SalvaModifiche();
            InviaAggiornamentoNetwork();
            ForzaAggiornamentoUI();
        }
    }
    wizard->Destroy();
}

// ============================================================================
// SALVATAGGIO & IMPORTAZIONE FILE JSON
// ============================================================================
void MagazzinoMainFrame::salvaa(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Salva il Magazzino in JSON", "", "magazzino.json",
                       "File JSON (*.json)|*.json", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
                       
    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

    ofstream file(saveFileDialog.GetPath().ToStdString());
    if (file.is_open()) {
        file << MagazzinoToJSON(m_reale);
        file.close();
        wxMessageBox("Dati esportati in formato JSON con successo!", "Salvataggio", wxOK | wxICON_INFORMATION, this);
    } else {
        wxMessageBox("Errore nell'apertura del file.", "Errore", wxOK | wxICON_ERROR, this);
    }
}

void MagazzinoMainFrame::importaa(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Importa File JSON", "", "",
                       "File JSON (*.json)|*.json", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
                       
    if (openFileDialog.ShowModal() == wxID_CANCEL) return;

    ifstream file(openFileDialog.GetPath().ToStdString());
    if (file.is_open()) {
        stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        if (JSONToMagazzino(m_reale, buffer.str())) {
            // Dopo l'importazione manuale, sincronizza immediatamente la rete e la UI aperta
            InviaAggiornamentoNetwork();
            ForzaAggiornamentoUI();
            wxMessageBox("File JSON importato e sincronizzato!", "Importazione", wxOK | wxICON_INFORMATION, this);
        } else {
            wxMessageBox("Il file non sembra essere un JSON valido per il magazzino.", "Errore Parsing", wxOK | wxICON_ERROR, this);
        }
    } else {
        wxMessageBox("Impossibile leggere il file selezionato.", "Errore", wxOK | wxICON_ERROR, this);
    }
}