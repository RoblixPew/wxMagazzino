#include <wx/wx.h>
#include "MagazzinoFrame.h"
#include "Magazzino.h"
#include "wxMagazzinoFrame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        Magazzino* istanzaMagazzino = new Magazzino();

        istanzaMagazzino->contap = 0;

        MagazzinoMainFrame* mainFrame = new MagazzinoMainFrame(nullptr, istanzaMagazzino);

        mainFrame->Show(true);

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
