#include "PlayScreen.h"

BEGIN_EVENT_TABLE(PlayScreen, wxPanel)
EVT_PAINT(PlayScreen::paintEvent)
EVT_BUTTON(2001, PlayScreen::OnPauseButtonClick)
EVT_TIMER(1000, PlayScreen::OnTimer)
EVT_ERASE_BACKGROUND(PlayScreen::OnEraseBackground)
EVT_LEFT_DOWN(PlayScreen::OnMouseLeftClick)
EVT_SHOW(PlayScreen::OnShow)
END_EVENT_TABLE()
#define INF 10000

PlayScreen::PlayScreen(Frame* parent, wxString file, wxBitmapType format) :
	wxPanel(parent, wxID_ANY), parentFrame(parent)
{
	image.LoadFile(file, format);

	wxBitmap bitmap;
	bitmap.LoadFile("PauseButton.png", wxBITMAP_TYPE_PNG);

	wxBitmapButton* pauseButton = new wxBitmapButton(this, 2001, bitmap, wxPoint(10, 10), wxDefaultSize);

	timer = new wxTimer(this, 1000);
		
}

PlayScreen::~PlayScreen()
{
	timer->Stop();
}

void PlayScreen::OnPauseButtonClick(wxCommandEvent & event)
{
	parentFrame->ShowPlayPause();
}

void PlayScreen::OnTimer(wxTimerEvent & event)
{
	if (bpm == 0)
	{
		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_int_distribution<> dist(0, 6);
		notasi = dist(e2);
		std::random_device rd2;
		std::mt19937 e3(rd2());
		std::uniform_int_distribution<> dist2(30, 50);
		bpm = dist2(e3);
		switch (notasi)
		{
		case 1:
			PaintObject.push_back(new Note(notasi, 110 + notasi * 55 + 25, 10));
			break;
		case 2:
			PaintObject.push_back(new Note(notasi, 110 + notasi * 55 + 55, 10));
			break;
		case 3:
			PaintObject.push_back(new Note(notasi, 110 + notasi * 55 + 100, 10));
			break;
		case 4:
			PaintObject.push_back(new Note(notasi, 110 + notasi * 55 + 140, 10));
			break;
		case 5:
			PaintObject.push_back(new Note(notasi, 110 + notasi * 55 + 176, 10));
			break;
		case 6:
			PaintObject.push_back(new Note(notasi, 110 + notasi * 55 + 197, 10));
			break;
		default :
			PaintObject.push_back(new Note(notasi, 110 + notasi * 55, 10));
			break;
		}
			
		
			
		
	}
	else
	{
		bpm--;
	}
	
	if (PaintObject.size()) {
		for (int i = 0; i < PaintObject.size(); i++)
		{
			PaintObject[i]->Move();
		}
		Refresh();
		for (int i = 0; i < PaintObject.size(); i++)
		{
			if (PaintObject[i]->getPos().y >= 310)
			{
				score--;
				PaintObject.erase(PaintObject.begin()+i);
				laststate = 0;
				break;
			}
		}
	}
	
}

void PlayScreen::paintEvent(wxPaintEvent & evt)
{
	wxBufferedPaintDC dc(this);
	PrepareDC(dc);
	render(dc);
	dc.SetFont(wxFont(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));
	if (laststate)
	{
		dc.SetTextForeground(*wxGREEN);
		dc.DrawText("Ok", 10, 90);
	}
	else
	{
		dc.SetTextForeground(*wxRED);
		dc.DrawText("Bad", 10, 90);
	}
	dc.SetTextForeground(*wxWHITE);
	dc.DrawText(wxString::Format("%d",score), 10, 50);
	if (PaintObject.size()) {
		for (int i = 0; i < PaintObject.size(); i++)
		{
			PaintObject[i]->Draw(dc);
		}
	}
}

void PlayScreen::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void PlayScreen::render(wxDC&  dc)
{
	dc.DrawBitmap(image, 0, 0, false);
}


void PlayScreen::OnEraseBackground(wxEraseEvent &event)
{

}

void PlayScreen::OnShow(wxShowEvent & event)
{
	if (this->m_isShown)
	{
		timer->Start(1);
		score = 0;
	}
	else
	{
		timer->Stop();
	}
}

void PlayScreen::OnMouseLeftClick(wxMouseEvent & event)
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
			if (PaintObject.size()) {
				if (PaintObject.front()->getJalur() == i)
				{
					if (PaintObject.front()->getPos().y < 310 && PaintObject.front()->getPos().y >= 290)
					{
						score+=2;
						laststate = 1;
					}
					else
					{
						score--;
						laststate = 0;
					}
				}
				else
				{
					score--;
					laststate = 0;
				}
				PaintObject.erase(PaintObject.begin());
			}
			else
			{
				score--;
				laststate = 0;
			}
			playSound(i);
			wxMessageOutputDebug().Printf("note %d, is intersecting", i);
			break;
		}

	}
}

bool PlayScreen::onSegment(wxPoint p, wxPoint q, wxPoint r)
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

int PlayScreen::orientation(wxPoint p, wxPoint q, wxPoint r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool PlayScreen::doIntersect(wxPoint p1, wxPoint q1, wxPoint p2, wxPoint q2)
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
bool PlayScreen::isInside(wxPoint polygon[], int n, wxPoint p)
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

void PlayScreen::playSound(int note)
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
	if(snd.IsOk())
		snd.Play(wxSOUND_ASYNC);
}



