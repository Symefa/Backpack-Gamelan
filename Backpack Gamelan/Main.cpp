#include "wx/wx.h"
#include "wx/wxprec.h"
#include "main.h"
#include "Frame.h"
#include "Title.h"

#ifndef WX_PRECOMP 
#include "wx/wx.h" 
#endif  

DECLARE_APP(MyApp)
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxInitAllImageHandlers();

	Frame *frame = new Frame(wxT("Backpack Gamelan"));

	frame->Show(true);

	return true;
}