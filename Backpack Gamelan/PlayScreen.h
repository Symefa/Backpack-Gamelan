#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <vector>
#include "Object.h"
#include "Frame.h"
#include "Note.h"
#include <random>

class PlayScreen : public wxPanel
{
	wxBitmap image;

public:
	PlayScreen(Frame* parent, wxString file, wxBitmapType format);
	~PlayScreen();

	void OnPauseButtonClick(wxCommandEvent& event);
	void OnTimer(wxTimerEvent &event);
	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void PlayScreen::OnEraseBackground(wxEraseEvent &event);
	void OnShow(wxShowEvent &event);
	void OnMouseLeftClick(wxMouseEvent &event);
	void render(wxDC& dc);

private:
	int laststate = 0;
	int score = 0;
	int notasi = 0;
	int bpm = 60;
	wxTimer *timer;
	std::vector <Object*> PaintObject;
	Frame *parentFrame;
	bool onSegment(wxPoint p, wxPoint q, wxPoint r);
	int orientation(wxPoint p, wxPoint q, wxPoint r);
	bool doIntersect(wxPoint p1, wxPoint q1, wxPoint p2, wxPoint q2);
	bool isInside(wxPoint polygon[], int n, wxPoint p);
	void playSound(int note);
	DECLARE_EVENT_TABLE()
};