#pragma once
#include <wx\dcbuffer.h>
class Object
{
public:
	Object();
	virtual void Draw(wxBufferedPaintDC &dc) = 0;
	virtual void Move() = 0;
	virtual wxPoint getPos() = 0;
	virtual int getJalur() = 0;
};

