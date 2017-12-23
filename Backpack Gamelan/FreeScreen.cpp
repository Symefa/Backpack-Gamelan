#include "FreeScreen.h"

BEGIN_EVENT_TABLE(FreeScreen, wxPanel)
EVT_PAINT(FreeScreen::paintEvent)
EVT_BUTTON(3001, FreeScreen::OnPauseButtonClick)
EVT_LEFT_DOWN(FreeScreen::OnMouseLeftClick)
END_EVENT_TABLE()

#define INF 10000

FreeScreen::FreeScreen(Frame* parent, wxString file, wxBitmapType format) :
	wxPanel(parent, wxID_ANY), parentFrame(parent)
{
	image.LoadFile(file, format);

	wxBitmap bitmap;
	bitmap.LoadFile("PauseButton.png", wxBITMAP_TYPE_PNG);

	wxBitmapButton* pauseButton = new wxBitmapButton(this, 3001, bitmap, wxPoint(10, 10), wxDefaultSize);
}

FreeScreen::~FreeScreen()
{

}

void FreeScreen::OnPauseButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowFreePause();
}

void FreeScreen::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void FreeScreen::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void FreeScreen::render(wxDC&  dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}

void FreeScreen::OnMouseLeftClick(wxMouseEvent & event)
{
	wxPoint ret[4];
	wxMessageOutputDebug().Printf("mouse event x = %d, y = %d", event.GetX(), event.GetY());
	wxPoint mouse = wxPoint(event.GetX(), event.GetY());
	for (int i = 0;i < 7;i++)
	{
		switch (i)
		{
		default:
			ret[0] = wxPoint(104, 331);
			ret[1] = wxPoint(164, 354);
			ret[2] = wxPoint(164, 582);
			ret[3] = wxPoint(1, 547);
			break;
		case 1:
			ret[0] = wxPoint(181, 331);
			ret[1] = wxPoint(251, 354);
			ret[2] = wxPoint(251, 582);
			ret[3] = wxPoint(121, 582);
			break;
		case 2:
			ret[0] = wxPoint(263, 354);
			ret[1] = wxPoint(342, 354);
			ret[2] = wxPoint(342, 582);
			ret[3] = wxPoint(243, 582);
			break;
		case 3:
			ret[0] = wxPoint(353, 354);
			ret[1] = wxPoint(442, 354);
			ret[2] = wxPoint(442, 582);
			ret[3] = wxPoint(353, 582);
			break;
		case 4:
			ret[0] = wxPoint(454, 354);
			ret[1] = wxPoint(541, 354);
			ret[2] = wxPoint(541, 582);
			ret[3] = wxPoint(454, 582);
			break;
		case 5:
			ret[0] = wxPoint(551, 354);
			ret[1] = wxPoint(623, 354);
			ret[2] = wxPoint(675, 582);
			ret[3] = wxPoint(574, 582);
			break;
		case 6:
			ret[0] = wxPoint(634, 354);
			ret[1] = wxPoint(695, 334);
			ret[2] = wxPoint(798, 513);
			ret[3] = wxPoint(695, 582);
			break;
		}

		if (isInside(ret, 4, mouse))
		{
			playSound(i);
			wxMessageOutputDebug().Printf("note %d, is intersecting", i);
			break;
		}

	}
	
}

bool FreeScreen::onSegment(wxPoint p, wxPoint q, wxPoint r)
{

	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;
	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise

int FreeScreen::orientation(wxPoint p, wxPoint q, wxPoint r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool FreeScreen::doIntersect(wxPoint p1, wxPoint q1, wxPoint p2, wxPoint q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

// Returns true if the wxPoint p lies inside the polygon[] with n vertices
bool FreeScreen::isInside(wxPoint polygon[], int n, wxPoint p)
{
	// There must be at least 3 vertices in polygon[]
	if (n < 3)  return false;

	// Create a wxPoint for line segment from p to infinite
	wxPoint extreme = { INF, p.y };

	// Count intersections of the above line with sides of polygon
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			// If the wxPoint 'p' is colinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise
	return count & 1;  // Same as (count%2 == 1)
}

void FreeScreen::playSound(int note)
{
	wxSound snd;
	switch (note)
	{
	default:
		snd.Create("SaronSl6l.wav");
		break;
	case 1:
		snd.Create("SaronSl1.wav");
		break;
	case 2:
		snd.Create("SaronSl2.wav");
		break;
	case 3:
		snd.Create("SaronSl3.wav");
		break;
	case 4:
		snd.Create("SaronSl5.wav");
		break;
	case 5:
		snd.Create("SaronSl6.wav");
		break;
	case 6:
		snd.Create("SaronSl1h.wav");
		break;
	}
	if (snd.IsOk())
		snd.Play(wxSOUND_ASYNC);
}
