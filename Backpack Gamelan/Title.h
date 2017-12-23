#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx\sound.h>
#include "Frame.h"

class Title : public wxPanel
{
	wxBitmap image;

public:
	Title(Frame* parent, wxString file, wxBitmapType format);
	~Title();

	void OnStartButtonClick(wxCommandEvent& event);

	void paintEvent(wxPaintEvent & evt);
	void paintNow();

	void render(wxDC& dc);

private:
	Frame *parentFrame;
	DECLARE_EVENT_TABLE()
};