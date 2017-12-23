#include "PausePlayScreen.h"

BEGIN_EVENT_TABLE(PausePlayScreen, wxPanel)
EVT_PAINT(PausePlayScreen::paintEvent)
EVT_BUTTON(5001, PausePlayScreen::OnBackButtonClick)
EVT_BUTTON(5002, PausePlayScreen::OnMenuButtonClick)
END_EVENT_TABLE()

PausePlayScreen::PausePlayScreen(Frame* parent, wxString file, wxBitmapType format) :
	wxPanel(parent, wxID_ANY), parentFrame(parent)
{
	image.LoadFile(file, format);

	wxBitmap bitmap1, bitmap2;
	bitmap1.LoadFile("ResumeButton.png", wxBITMAP_TYPE_PNG);
	bitmap2.LoadFile("MainMenuButton.png", wxBITMAP_TYPE_PNG);

	wxBitmapButton* pauseButton = new wxBitmapButton(this, 5001, bitmap1, wxPoint(275, 225), wxDefaultSize);
	wxBitmapButton* menuButton = new wxBitmapButton(this, 5002, bitmap2, wxPoint(225, 325), wxDefaultSize);
}

PausePlayScreen::~PausePlayScreen()
{

}

void PausePlayScreen::OnBackButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowPlay();
}

void PausePlayScreen::OnMenuButtonClick(wxCommandEvent & event)
{

	parentFrame->ShowMenu();
	wxSound snd;
	snd.Create("SaronSl6.wav");
	if (snd.IsOk())
		snd.Play(wxSOUND_ASYNC);
}

void PausePlayScreen::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void PausePlayScreen::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void PausePlayScreen::render(wxDC&  dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}