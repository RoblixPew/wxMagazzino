#pragma once
using namespace std;
#include "wxMagazzinoFrame.h"
#include "Magazzino.h"
#include <wx/socket.h>
#include <thread>
#include <atomic>

// Forward declaration per la classe della lista
class MagazzinoUIList;

class MagazzinoMainFrame : public m_MainFrame {
private:
    Magazzino* m_reale;
    
    // Gestione di Rete & Sincronizzazione
    int m_portoAscolto;
    int m_portoDestinazione;
    thread m_serverThread;
    atomic<bool> m_running;
    
    // Puntatore alla vista della lista per aggiornamenti real-time
    MagazzinoUIList* m_listaAperta;

public:
    MagazzinoMainFrame(wxWindow* parent, Magazzino* istanzaDati);
    ~MagazzinoMainFrame();

    // Metodi pubblici di sincronizzazione richiamabili dalle sotto-finestre
    void InviaAggiornamentoNetwork();
    void ForzaAggiornamentoUI();

protected:
    void AddProductFrame(wxCommandEvent& event) override;
    void ShowProductFrame(wxCommandEvent& event) override;
    void RemoveProductFrame(wxCommandEvent& event) override;
    void ModifyProductFrame(wxCommandEvent& event) override;
    void salvaa(wxCommandEvent& event) override;
    void importaa(wxCommandEvent& event) override;

    // Event handler interno per i messaggi cross-thread provenienti dal socket
    void OnNetworkUpdateEvent(wxCommandEvent& event);
};