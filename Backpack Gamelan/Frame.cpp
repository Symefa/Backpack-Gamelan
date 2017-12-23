#include "wx/wx.h"
#include "Frame.h"
#include "Title.h"
#include "Menu.h"
#include "PlayScreen.h"
#include "FreeScreen.h"
#include "HistoryScreen.h"
#include "PausePlayScreen.h"
#include "PauseFreeScreen.h"

Frame::Frame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 640))
{
	this->InitComponents();
	SetIcon(wxICON(frame_icon));
	Centre();
}

void Frame::fitWindowSize()
{
	this->boxSizer->Fit(this);
	this->boxSizer->SetSizeHints(this);
	this->SetSize(wxSize(800, 640));
	this->Layout();
}

void Frame::InitComponents()
{
	boxSizer = new wxBoxSizer(wxVERTICAL);

	this->titleScreen = new Title(this, wxT("TitleScreen.png"), wxBITMAP_TYPE_PNG);
	this->titleScreen->Show(false);
	this->boxSizer->Add(titleScreen, 1, wxEXPAND, 0);

	this->menu = new Menu(this, wxT("Menu.png"), wxBITMAP_TYPE_PNG);
	this->menu->Show(false);
	this->boxSizer->Add(menu, 1, wxEXPAND, 0);

	this->play = new PlayScreen(this, wxT("Play.png"), wxBITMAP_TYPE_PNG);
	this->play->Show(false);
	this->boxSizer->Add(play, 1, wxEXPAND, 0);

	this->free = new FreeScreen(this, wxT("Free.png"), wxBITMAP_TYPE_PNG);
	this->free->Show(false);
	this->boxSizer->Add(free, 1, wxEXPAND, 0);

	this->history = new HistoryScreen(this, wxT("History.png"), wxBITMAP_TYPE_PNG);
	this->history->Show(false);
	this->boxSizer->Add(history, 1, wxEXPAND, 0);

	this->pausePlay = new PausePlayScreen(this, wxT("Pause.png"), wxBITMAP_TYPE_PNG);
	this->pausePlay->Show(false);
	this->boxSizer->Add(pausePlay, 1, wxEXPAND, 0);

	this->pauseFree = new PauseFreeScreen(this, wxT("Pause.png"), wxBITMAP_TYPE_PNG);
	this->pauseFree->Show(false);
	this->boxSizer->Add(pauseFree, 1, wxEXPAND, 0);

	SetSizer(boxSizer);

	ShowTitle();
}

void Frame::ShowTitle()
{
	this->titleScreen->Show(true);
	this->menu->Show(false);
	this->play->Show(false);
	this->free->Show(false);
	this->history->Show(false);
	this->pausePlay->Show(false);
	this->pauseFree->Show(false);
	fitWindowSize();
}

void Frame::ShowMenu()
{
	this->titleScreen->Show(false);
	this->menu->Show(true);
	this->play->Show(false);
	this->free->Show(false);
	this->history->Show(false);
	this->pausePlay->Show(false);
	this->pauseFree->Show(false);
	fitWindowSize();
}

void Frame::ShowPlay()
{
	this->titleScreen->Show(false);
	this->menu->Show(false);
	this->play->Show(true);
	this->free->Show(false);
	this->history->Show(false);
	this->pausePlay->Show(false);

	fitWindowSize();
}

void Frame::ShowFree()
{
	this->titleScreen->Show(false);
	this->menu->Show(false);
	this->play->Show(false);
	this->free->Show(true);
	this->history->Show(false);
	this->pausePlay->Show(false);
	this->pauseFree->Show(false);

	fitWindowSize();
}

void Frame::ShowHistory()
{
	this->titleScreen->Show(false);
	this->menu->Show(false);
	this->play->Show(false);
	this->free->Show(false);
	this->history->Show(true);
	this->pausePlay->Show(false);

	fitWindowSize();
}

void Frame::ShowPlayPause()
{
	this->titleScreen->Show(false);
	this->menu->Show(false);
	this->play->Show(false);
	this->free->Show(false);
	this->history->Show(false);
	this->pausePlay->Show(true);

	fitWindowSize();
}

void Frame::ShowFreePause()
{
	this->titleScreen->Show(false);
	this->menu->Show(false);
	this->play->Show(false);
	this->free->Show(false);
	this->history->Show(false);
	this->pausePlay->Show(false);
	this->pauseFree->Show(true);

	fitWindowSize();
}