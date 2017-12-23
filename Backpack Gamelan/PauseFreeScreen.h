#include <wx/wx.h>
#include <wx/sizer.h>
#include "Frame.h"
#include <wx\sound.h>

class PauseFreeScreen : public wxPanel
{
	wxBitmap image;

public:
	PauseFreeScreen(Frame* parent, wxString file, wxBitmapType format);
	~PauseFreeScreen();

	void OnBackButtonClick(wxCommandEvent& event);
	void OnMenuButtonClick(wxCommandEvent& event);

	void paintEvent(wxPaintEvent & evt);
	void paintNow();

	void render(wxDC& dc);

private:
	Frame *parentFrame;
	DECLARE_EVENT_TABLE()
};