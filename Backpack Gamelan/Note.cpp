#include "Note.h"



Note::Note(int jalur, int x, int y)
{
	this->x = x; this->y = y; this->jalur = jalur;
}

void Note::Draw(wxBufferedPaintDC & dc)
{
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawRectangle(wxPoint(x, y), wxSize(width, height));
}

void Note::Move()
{
	y++;
}

wxPoint Note::getPos()
{
	return wxPoint(x,y);
}

int Note::getJalur()
{
	return jalur;
}


Note::~Note()
{
}


