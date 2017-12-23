#include <wx/wx.h>
#include <wx/sizer.h>
#include "Frame.h"

class HistoryScreen : public wxPanel
{
	wxBitmap image;

public:
	HistoryScreen(Frame* parent, wxString file, wxBitmapType format);
	~HistoryScreen();

	void OnBackButtonClick(wxCommandEvent& event);

	void paintEvent(wxPaintEvent & evt);
	void paintNow();

	void render(wxDC& dc);

private:
	Frame *parentFrame;
	DECLARE_EVENT_TABLE()
};