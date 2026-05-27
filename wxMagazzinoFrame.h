///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/wizard.h>
#include <wx/dynarray.h>
WX_DEFINE_ARRAY_PTR( wxWizardPageSimple*, WizardPages );
#include <wx/dataview.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class m_MainFrame
///////////////////////////////////////////////////////////////////////////////
class m_MainFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* m_label1;
		wxButton* m_btnadd;
		wxButton* m_btnlist;
		wxButton* m_btnremove;
		wxButton* m_btnmodify;
		wxButton* m_salva;
		wxButton* m_importa;

		// Virtual event handlers, override them in your derived class
		virtual void AddProductFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void ShowProductFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void RemoveProductFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void ModifyProductFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void salvaa( wxCommandEvent& event ) { event.Skip(); }
		virtual void importaa( wxCommandEvent& event ) { event.Skip(); }


	public:

		m_MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 547,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~m_MainFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class m_WizardModify
///////////////////////////////////////////////////////////////////////////////
class m_WizardModify : public wxWizard
{
	private:

	protected:
		wxStaticText* m_staticText16;
		wxTextCtrl* m_TxtCtrlProduct2modify;
		wxStaticText* m_ProdottoNonTrovato;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_txtproductname2modify;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_txtproductprice2modify;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_txtproductquantiy2modify;

	public:

		m_WizardModify( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Modifica Prodotto"), const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE );
		WizardPages m_pages;

		~m_WizardModify();

};

///////////////////////////////////////////////////////////////////////////////
/// Class m_FrameRemoveProduct
///////////////////////////////////////////////////////////////////////////////
class m_FrameRemoveProduct : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* m_txtctrl2remove;
		wxButton* m_RemoveProduct;
		wxStaticText* m_RemovedProduct;

		// Virtual event handlers, override them in your derived class
		virtual void RemoveProduct( wxCommandEvent& event ) { event.Skip(); }


	public:

		m_FrameRemoveProduct( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Rimuovi Prodotto"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~m_FrameRemoveProduct();

};

///////////////////////////////////////////////////////////////////////////////
/// Class m_FrameAddProduct
///////////////////////////////////////////////////////////////////////////////
class m_FrameAddProduct : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* m_txtnomeadd;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_txtprezzoadd;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_txtquantitaadd;
		wxButton* m_button5;

		// Virtual event handlers, override them in your derived class
		virtual void AggiungiProdotto( wxCommandEvent& event ) { event.Skip(); }


	public:

		m_FrameAddProduct( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Aggiungi Prodotto"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~m_FrameAddProduct();

};

///////////////////////////////////////////////////////////////////////////////
/// Class m_FrameProductList
///////////////////////////////////////////////////////////////////////////////
class m_FrameProductList : public wxFrame
{
	private:

	protected:
		wxDataViewCtrl* m_dataViewCtrl5;
		wxDataViewColumn* m_dataViewColumnProduct;
		wxDataViewColumn* m_dataViewColumnPrice;
		wxDataViewColumn* m_dataViewColumnQuantity;

	public:

		m_FrameProductList( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Lista Prodotti"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~m_FrameProductList();

};

