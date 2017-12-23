#include "HistoryScreen.h"

BEGIN_EVENT_TABLE(HistoryScreen, wxPanel)
EVT_PAINT(HistoryScreen::paintEvent)
EVT_BUTTON(4001, HistoryScreen::OnBackButtonClick)
END_EVENT_TABLE()

HistoryScreen::HistoryScreen(Frame* parent, wxString file, wxBitmapType format) :
	wxPanel(parent, wxID_ANY), parentFrame(parent)
{
	image.LoadFile(file, format);

	wxBitmap bitmap;
	bitmap.LoadFile("Back.png", wxBITMAP_TYPE_PNG);

	wxBitmapButton* backButton = new wxBitmapButton(this, 4001, bitmap, wxPoint(10, 10), wxDefaultSize);
}

HistoryScreen::~HistoryScreen()
{

}

void HistoryScreen::OnBackButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowMenu();
}

void HistoryScreen::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void HistoryScreen::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void HistoryScreen::render(wxDC&  dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}