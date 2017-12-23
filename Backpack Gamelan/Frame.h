#ifndef _FRAME_H_
#define _FRAME_H_
#include <wx/wx.h>

class Title;
class Menu;
class PlayScreen;
class FreeScreen;
class HistoryScreen;
class PausePlayScreen;
class PauseFreeScreen;

class Frame:public wxFrame
{
private:
	wxBoxSizer* boxSizer;
	Title* titleScreen;
	Menu* menu;
	PlayScreen* play;
	FreeScreen* free;
	HistoryScreen* history;
	PausePlayScreen* pausePlay;
	PauseFreeScreen* pauseFree;

	void fitWindowSize();
public:
	Frame(const wxString& title);
	void InitComponents();
	void ShowTitle();
	void ShowMenu();
	void ShowPlay();
	void ShowFree();
	void ShowHistory();
	void ShowPlayPause();
	void ShowFreePause();
};

#endif // _FRAME_H_