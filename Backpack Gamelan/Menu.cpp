#include "Menu.h"


BEGIN_EVENT_TABLE(Menu, wxPanel)
	EVT_PAINT(Menu::paintEvent)
	EVT_BUTTON(1002, Menu::OnPlayButtonClick)
	EVT_BUTTON(1003, Menu::OnFreeButtonClick)
	EVT_BUTTON(1004, Menu::OnHistoryButtonClick)
END_EVENT_TABLE()

Menu::Menu(Frame* parent, wxString file, wxBitmapType format) :
	wxPanel(parent, wxID_ANY), parentFrame(parent)
{
	image.LoadFile(file, format);

	wxBitmap bitmap1, bitmap2, bitmap3;
	bitmap1.LoadFile("PlayButton.png", wxBITMAP_TYPE_PNG);
	bitmap2.LoadFile("FreeButton.png", wxBITMAP_TYPE_PNG);
	bitmap3.LoadFile("HistoryButton.png", wxBITMAP_TYPE_PNG);

	wxBitmapButton* playButton = new wxBitmapButton(this, 1002, bitmap1, wxPoint(50, 205), wxDefaultSize);
	wxBitmapButton* freeButton = new wxBitmapButton(this, 1003, bitmap2, wxPoint(313, 280), wxDefaultSize);
	wxBitmapButton* historyButton = new wxBitmapButton(this, 1004, bitmap3, wxPoint(553, 370), wxDefaultSize);
}

Menu::~Menu()
{

}

void Menu::OnPlayButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowPlay();
	wxSound snd;
	snd.Create("SaronSl2.wav");
	if (snd.IsOk())
	snd.Play(wxSOUND_ASYNC);
}

void Menu::OnFreeButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowFree();
	wxSound snd;
	snd.Create("SaronSl3.wav");
	if (snd.IsOk())
	snd.Play(wxSOUND_ASYNC);
}

void Menu::OnHistoryButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowHistory();
	wxSound snd;
	snd.Create("SaronSl5.wav");
	if (snd.IsOk())
	snd.Play(wxSOUND_ASYNC);
}

void Menu::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void Menu::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void Menu::render(wxDC&  dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}