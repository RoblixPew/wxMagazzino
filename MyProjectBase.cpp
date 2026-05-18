///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyProjectBase.h"

///////////////////////////////////////////////////////////////////////////

m_MainFrame::m_MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 3, 0, 0 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

	m_label1 = new wxStaticText( this, wxID_ANY, _(" PROGRAMMA MAGAZZINO "), wxDefaultPosition, wxDefaultSize, 0 );
	m_label1->Wrap( -1 );
	gSizer1->Add( m_label1, 0, wxALL, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

	m_btnadd = new wxButton( this, wxID_ANY, _("Aggiungi Prodotto"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_btnadd, 0, wxALL, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

	m_btnlist = new wxButton( this, wxID_ANY, _("Mostra Prodotti"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_btnlist, 0, wxALL, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

	m_btnremove = new wxButton( this, wxID_ANY, _("Rimuovi Prodotto"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_btnremove, 0, wxALL, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

	m_btnmodify = new wxButton( this, wxID_ANY, _("Modifica Prodotto"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_btnmodify, 0, wxALL, 5 );


	this->SetSizer( gSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_btnadd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_MainFrame::AddProductFrame ), NULL, this );
	m_btnlist->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_MainFrame::ShowProductFrame ), NULL, this );
	m_btnremove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_MainFrame::RemoveProductFrame ), NULL, this );
	m_btnmodify->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_MainFrame::ModifyProductFrame ), NULL, this );
}

m_MainFrame::~m_MainFrame()
{
}

m_WizardModify::m_WizardModify( wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style )
{
	this->Create( parent, id, title, bitmap, pos, style );

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxWizardPageSimple* m_wizPage2 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage2 );

	wxGridSizer* gSizer12;
	gSizer12 = new wxGridSizer( 3, 2, 0, 0 );


	gSizer12->Add( 0, 0, 1, wxEXPAND, 5 );


	gSizer12->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText16 = new wxStaticText( m_wizPage2, wxID_ANY, _("Inserire Nome Prodotto Da Modificare"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	gSizer12->Add( m_staticText16, 0, wxALL, 5 );


	gSizer12->Add( 0, 0, 1, wxEXPAND, 5 );

	m_TxtCtrlProduct2modify = new wxTextCtrl( m_wizPage2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer12->Add( m_TxtCtrlProduct2modify, 0, wxALL, 5 );

	m_ProdottoNonTrovato = new wxStaticText( m_wizPage2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_ProdottoNonTrovato->Wrap( -1 );
	gSizer12->Add( m_ProdottoNonTrovato, 0, wxALL, 5 );


	m_wizPage2->SetSizer( gSizer12 );
	m_wizPage2->Layout();
	gSizer12->Fit( m_wizPage2 );
	wxWizardPageSimple* m_wizPage3 = new wxWizardPageSimple( this );
	m_pages.Add( m_wizPage3 );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText2 = new wxStaticText( m_wizPage3, wxID_ANY, _("Prodotto:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer2->Add( m_staticText2, 0, wxALL, 5 );

	m_txtproductname2modify = new wxTextCtrl( m_wizPage3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_txtproductname2modify, 0, wxALL, 5 );

	m_staticText3 = new wxStaticText( m_wizPage3, wxID_ANY, _("Prezzo:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer2->Add( m_staticText3, 0, wxALL, 5 );

	m_txtproductprice2modify = new wxTextCtrl( m_wizPage3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_txtproductprice2modify, 0, wxALL, 5 );

	m_staticText4 = new wxStaticText( m_wizPage3, wxID_ANY, _("Quantità:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer2->Add( m_staticText4, 0, wxALL, 5 );

	m_txtproductquantiy2modify = new wxTextCtrl( m_wizPage3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_txtproductquantiy2modify, 0, wxALL, 5 );


	gSizer2->Add( 0, 0, 1, wxEXPAND, 5 );


	m_wizPage3->SetSizer( gSizer2 );
	m_wizPage3->Layout();
	gSizer2->Fit( m_wizPage3 );

	this->Centre( wxBOTH );

	for ( unsigned int i = 1; i < m_pages.GetCount(); i++ )
	{
		m_pages.Item( i )->SetPrev( m_pages.Item( i - 1 ) );
		m_pages.Item( i - 1 )->SetNext( m_pages.Item( i ) );
	}
}

m_WizardModify::~m_WizardModify()
{
	m_pages.Clear();
}

m_FrameRemoveProduct::m_FrameRemoveProduct( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 5, 1, 0, 0 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Inserisci Nome Prodotto Da Rimuovere:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer2->Add( m_staticText2, 0, wxALL, 5 );

	m_txtctrl2remove = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_txtctrl2remove, 0, wxALL, 5 );

	m_RemoveProduct = new wxButton( this, wxID_ANY, _("Rimuovi Prodotto"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_RemoveProduct, 0, wxALL, 5 );

	m_RemovedProduct = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_RemovedProduct->Wrap( -1 );
	gSizer2->Add( m_RemovedProduct, 0, wxALL, 5 );


	this->SetSizer( gSizer2 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_RemoveProduct->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_FrameRemoveProduct::RemoveProduct ), NULL, this );
}

m_FrameRemoveProduct::~m_FrameRemoveProduct()
{
}

m_FrameAddProduct::m_FrameAddProduct( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Prodotto:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer2->Add( m_staticText2, 0, wxALL, 5 );

	m_txtnomeadd = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_txtnomeadd, 0, wxALL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Prezzo:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer2->Add( m_staticText3, 0, wxALL, 5 );

	m_txtprezzoadd = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_txtprezzoadd, 0, wxALL, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Quantità:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer2->Add( m_staticText4, 0, wxALL, 5 );

	m_txtquantitàadd = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_txtquantitàadd, 0, wxALL, 5 );


	gSizer2->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button5 = new wxButton( this, wxID_ANY, _("Aggiungi Prodotto"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_button5, 0, wxALL, 5 );


	this->SetSizer( gSizer2 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_FrameAddProduct::AggiungiProdotto ), NULL, this );
}

m_FrameAddProduct::~m_FrameAddProduct()
{
}

m_FrameProductList::m_FrameProductList( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_dataViewCtrl5 = new wxDataViewCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 400,250 ), 0 );
	m_dataViewColumnProduct = m_dataViewCtrl5->AppendTextColumn( _("Prodotto"), 0, wxDATAVIEW_CELL_INERT, 200, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE );
	m_dataViewColumnPrice = m_dataViewCtrl5->AppendTextColumn( _("Prezzo"), 0, wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE );
	m_dataViewColumnQuantity = m_dataViewCtrl5->AppendTextColumn( _("Quantità"), 0, wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE );
	bSizer6->Add( m_dataViewCtrl5, 1, wxALL, 5 );


	this->SetSizer( bSizer6 );
	this->Layout();

	this->Centre( wxBOTH );
}

m_FrameProductList::~m_FrameProductList()
{
}
