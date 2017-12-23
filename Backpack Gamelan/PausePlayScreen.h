#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx\sound.h>
#include "Frame.h"

class PausePlayScreen : public wxPanel
{
	wxBitmap image;

public:
	PausePlayScreen(Frame* parent, wxString file, wxBitmapType format);
	~PausePlayScreen();

	void OnBackButtonClick(wxCommandEvent& event);
	void OnMenuButtonClick(wxCommandEvent& event);

	void paintEvent(wxPaintEvent & evt);
	void paintNow();

	void render(wxDC& dc);

private:
	Frame *parentFrame;
	DECLARE_EVENT_TABLE()
};