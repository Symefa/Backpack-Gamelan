#include <wx/wx.h>
#include <wx/sizer.h>
#include "Frame.h"
#include <wx\sound.h>

class FreeScreen : public wxPanel
{
	wxBitmap image;

public:
	FreeScreen(Frame* parent, wxString file, wxBitmapType format);
	~FreeScreen();

	void OnPauseButtonClick(wxCommandEvent& event);

	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void OnMouseLeftClick(wxMouseEvent &event);
	void render(wxDC& dc);

private:
	wxPoint mousePos;
	void mouseMoved(wxMouseEvent &event);
	Frame *parentFrame;
	bool onSegment(wxPoint p, wxPoint q, wxPoint r);
	int orientation(wxPoint p, wxPoint q, wxPoint r);
	bool doIntersect(wxPoint p1, wxPoint q1, wxPoint p2, wxPoint q2);
	bool isInside(wxPoint polygon[], int n, wxPoint p);
	void playSound(int note);
	DECLARE_EVENT_TABLE()
};