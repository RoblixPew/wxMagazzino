#include <wx/wx.h>
#include "MagazzinoFrame.cpp"
#include "Magazzino.h"
#include "MyProjectBase.h"
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
