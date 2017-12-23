#pragma once
#include <wx\dcbuffer.h>
#include "wx\sound.h"
#include <wx\string.h>
#include "Object.h"
class Note : public Object
{
public:
	Note(int jalur,int x, int y);
	virtual void Draw(wxBufferedPaintDC &dc);
	virtual void Move();
	wxPoint getPos();
	virtual int getJalur();
	~Note();
private:
	int x, y, jalur;
	int width = 55, height = 15;
};

