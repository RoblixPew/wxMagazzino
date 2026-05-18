#include "MyProjectBase.h"
#include "Magazzino.h"
#include <wx/msgdlg.h>
#include <wx/dataview.h>
#include <string>

using namespace std;

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
            wxString nomeEsistente(m_reale->p.nomeprodotto[i]);

            if (nomeEsistente.CmpNoCase(nomeWx) == 0) {
                wxMessageBox("Errore: Un prodotto con questo nome è già presente nel magazzino!", "Prodotto Duplicato", wxOK | wxICON_WARNING, this);
                return; 
            }
        }


        string prezzoStr = m_txtprezzoadd->GetValue().ToStdString();
        try {
            m_reale->p.prezzo[m_reale->contap] = stod(prezzoStr);
        } catch (...) {
            wxMessageBox("Errore: Il prezzo inserito non è valido!", "Errore Input", wxOK | wxICON_ERROR, this);
            return;
        }

        string quantitaStr = m_txtquantitàadd->GetValue().ToStdString(); 
        try {
            m_reale->p.quantita[m_reale->contap] = stoi(quantitaStr);
        } catch (...) {
            wxMessageBox("Errore: La quantità inserita non è valida!", "Errore Input", wxOK | wxICON_ERROR, this);
            return;
        }
        

        m_reale->p.nomeprodotto[m_reale->contap] = nuovoNome;
        m_reale->contap += 1;
        
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
            if (m_reale->p.nomeprodotto[i] == daRimuovere) {
                indiceTrovato = i;
                break;
            }
        }

        if (indiceTrovato == -1) {
            m_RemovedProduct->SetLabel("Prodotto non trovato nel magazzino!");
            return;
        }

        for (int i = indiceTrovato; i < m_reale->contap - 1; i++) {
            m_reale->p.nomeprodotto[i] = m_reale->p.nomeprodotto[i + 1];
            m_reale->p.prezzo[i] = m_reale->p.prezzo[i + 1];
            m_reale->p.quantita[i] = m_reale->p.quantita[i + 1];
        }

        m_reale->contap -= 1;
        wxMessageBox("Prodotto rimosso con successo!", "Successo", wxOK | wxICON_INFORMATION, this);
        this->Close();
    }
};

// ==========================================
// 3. FINESTRA MOSTRA PRODOTTI (TABELLA CORRETTA)
// ==========================================
class MagazzinoUIList : public m_FrameProductList {
public:
    MagazzinoUIList(wxWindow* parent, Magazzino* istanzaDati) : m_FrameProductList(parent) {
        wxDataViewListStore* store = new wxDataViewListStore();
        m_dataViewCtrl5->ClearColumns();
        m_dataViewCtrl5->AssociateModel(store);
        store->DecRef(); 

        m_dataViewCtrl5->AppendTextColumn("Prodotto", 0, wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT);
        m_dataViewCtrl5->AppendTextColumn("Prezzo", 1, wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT);
        m_dataViewCtrl5->AppendTextColumn(wxT("Quantità"), 2, wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT);

        for (int i = 0; i < istanzaDati->contap; i++) {
            wxVector<wxVariant> data;
            data.push_back(wxVariant(istanzaDati->p.nomeprodotto[i]));
            data.push_back(wxVariant(wxString::Format(wxT("%.2f €"), istanzaDati->p.prezzo[i])));
            data.push_back(wxVariant(wxString::Format(wxT("%d"), istanzaDati->p.quantita[i])));
            store->AppendItem(data);
        }
    }
};


// ==========================================
// 4. PROCEDURA GUIDATA MODIFICA (WIZARD CON VALIDAZIONE)
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
                if (m_reale->p.nomeprodotto[i] == nomeDaCercare) {
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
            m_txtproductname2modify->SetValue(m_reale->p.nomeprodotto[m_indiceTrovato]);
            m_txtproductprice2modify->SetValue(wxString::Format(wxT("%.2f"), m_reale->p.prezzo[m_indiceTrovato]));
            m_txtproductquantiy2modify->SetValue(wxString::Format(wxT("%d"), m_reale->p.quantita[m_indiceTrovato]));
        }
    }

    void SalvaModifiche() {
        if (m_indiceTrovato != -1) {
            try {
                string nuovoNome = m_txtproductname2modify->GetValue().ToStdString();
                double nuovoPrezzo = stod(m_txtproductprice2modify->GetValue().ToStdString());
                int nuovaQuantita = stoi(m_txtproductquantiy2modify->GetValue().ToStdString());

                m_reale->p.nomeprodotto[m_indiceTrovato] = nuovoNome;
                m_reale->p.prezzo[m_indiceTrovato] = nuovoPrezzo;
                m_reale->p.quantita[m_indiceTrovato] = nuovaQuantita;

                wxMessageBox("Prodotto modificato con successo!", "Successo", wxOK | wxICON_INFORMATION, this);
            } catch (...) {
                wxMessageBox("Errore: I dati numerici immessi non sono validi!", "Errore Modifica", wxOK | wxICON_ERROR, this);
            }
        }
    }
};

// ==========================================
// 5. FINESTRA PRINCIPALE (MAIN FRAME)
// ==========================================
class MagazzinoMainFrame : public m_MainFrame {
private:
    Magazzino* m_reale;

public:
    MagazzinoMainFrame(wxWindow* parent, Magazzino* istanzaDati) : m_MainFrame(parent) {
        m_reale = istanzaDati;
    }

protected:
    void AddProductFrame(wxCommandEvent& event) override {
        MagazzinoUIAdd* frameAdd = new MagazzinoUIAdd(this, m_reale);
        frameAdd->Show(true);
    }

    void ShowProductFrame(wxCommandEvent& event) override {
        MagazzinoUIList* frameList = new MagazzinoUIList(this, m_reale);
        frameList->Show(true);
    }

    void RemoveProductFrame(wxCommandEvent& event) override {
        MagazzinoUIRemove* frameRemove = new MagazzinoUIRemove(this, m_reale);
        frameRemove->Show(true);
    }

    void ModifyProductFrame(wxCommandEvent& event) override {
        MagazzinoUIWizard* wizard = new MagazzinoUIWizard(this, m_reale);
        
        if (wizard->m_pages.GetCount() > 0) {
            wxWizardPage* firstPage = dynamic_cast<wxWizardPage*>(wizard->m_pages.Item(0));
            
            if (wizard->RunWizard(firstPage)) {
                wizard->SalvaModifiche();
            }
        }
        wizard->Destroy();
    }
};
