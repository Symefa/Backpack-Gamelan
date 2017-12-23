#include "PauseFreeScreen.h"

BEGIN_EVENT_TABLE(PauseFreeScreen, wxPanel)
EVT_PAINT(PauseFreeScreen::paintEvent)
EVT_BUTTON(6001, PauseFreeScreen::OnBackButtonClick)
EVT_BUTTON(6002, PauseFreeScreen::OnMenuButtonClick)
END_EVENT_TABLE()

PauseFreeScreen::PauseFreeScreen(Frame* parent, wxString file, wxBitmapType format) :
	wxPanel(parent, wxID_ANY), parentFrame(parent)
{
	image.LoadFile(file, format);

	wxBitmap bitmap1, bitmap2;
	bitmap1.LoadFile("ResumeButton.png", wxBITMAP_TYPE_PNG);
	bitmap2.LoadFile("MainMenuButton.png", wxBITMAP_TYPE_PNG);

	wxBitmapButton* pauseButton = new wxBitmapButton(this, 6001, bitmap1, wxPoint(275, 225), wxDefaultSize);
	wxBitmapButton* menuButton = new wxBitmapButton(this, 6002, bitmap2, wxPoint(225, 325), wxDefaultSize);
}

PauseFreeScreen::~PauseFreeScreen()
{

}

void PauseFreeScreen::OnBackButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowFree();
}

void PauseFreeScreen::OnMenuButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowMenu();
	wxSound snd;
	snd.Create("SaronSl6.wav");
	if (snd.IsOk())
		snd.Play(wxSOUND_ASYNC);
}

void PauseFreeScreen::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void PauseFreeScreen::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void PauseFreeScreen::render(wxDC&  dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}