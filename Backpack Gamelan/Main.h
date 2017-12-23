#ifndef _APP_H_
#define _APP_H_

#ifndef WX_PRECOMP 
#include "wx/wx.h" 
#endif  

#include "wx/wxprec.h"
#include "Frame.h"

class MyApp:public wxApp
{
public:
	virtual bool OnInit();
};

#endif // _APP_H_