#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx\sound.h>
#include "Frame.h"

class Menu : public wxPanel
{
	wxBitmap image;

public:
	Menu(Frame* parent, wxString file, wxBitmapType format);
	~Menu();

	void OnPlayButtonClick(wxCommandEvent& event);
	void OnFreeButtonClick(wxCommandEvent& event);
	void OnHistoryButtonClick(wxCommandEvent& event);

	void paintEvent(wxPaintEvent & evt);
	void paintNow();

	void render(wxDC& dc);

private:
	Frame *parentFrame;
	DECLARE_EVENT_TABLE()
};