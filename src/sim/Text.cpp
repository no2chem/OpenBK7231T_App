#ifdef WINDOWS
#include "Text.h"

void CText::recalcBoundsSelf() {
	bounds.clear();
	int line = 0;
	int ch = 0;;
	char buffer[512];
	CMD_ExpandConstantsWithinString(txt.c_str(), buffer, sizeof(buffer));
	const char *p = buffer;
	bounds.addPoint(Coord(0, -8));
	// do not go smaller than that
	bounds.addPoint(Coord(9, 5));
	while (*p) {
		if (p[0] == '\n') {
			line++;
			ch = 0;
		}
		else {
			ch++;
		}
		bounds.addPoint(Coord(9 * ch, 5 + 15 * line));
		p++;
	}
	//int useLen = txt.size();
	//if (bTextEditMode)
	//	useLen += 1;
	//bounds.addPoint(Coord(9 * useLen, 5));
	//bounds.addPoint(Coord(0, -8));
}
CShape *CText::cloneShape() {
	CText *r = new CText();
	r->pos = this->pos;
	r->txt = this->txt;
	this->cloneShapeTo(r);
	return r;
}
bool CText::processKeyDown(int keyCode) {
	if (keyCode == SDLK_BACKSPACE) {
		if (cursorPos > 0) {
			txt.erase(cursorPos-1, 1);
			cursorPos--;
		}
	}
	if (keyCode == SDLK_DELETE) {
		if (txt.size() > cursorPos) {
			txt.erase(cursorPos, 1);
		}
	}
	if (keyCode == SDLK_RIGHT) {
		cursorPos++;
		if (cursorPos > txt.size())
			cursorPos = txt.size();
	}
	if (keyCode == SDLK_LEFT) {
		cursorPos--;
		if (cursorPos < 0)
			cursorPos = 0;
	}
	if (keyCode == SDLK_ESCAPE) {
		return true;
	}
	if (keyCode == SDLK_RETURN) {
		appendText("\n");
	}
	return false;
}
void CText::appendText(const char *s) {
	//txt.append(s);
	txt.insert(cursorPos, s);
	cursorPos += strlen(s);
	recalcBoundsSelf();
}


void CText::drawShape() {
	char buffer[512];
	if (bTextEditMode) {
		recalcBoundsSelf();
	}
	if (bTextEditMode) {
		strncpy(buffer, txt.c_str(), cursorPos);
		buffer[cursorPos] = 0;
		strcat(buffer, "|");
		strcat(buffer, txt.c_str()+ cursorPos);
		drawText(getX(), getY(), buffer);
	}
	else {
		drawText(getX(), getY(), txt.c_str());
	}
}



float CText::drawPrivateInformation2D(float x, float h) {
	h = drawText(x, h, "Text: %s", this->txt.c_str());
	return h;
}


void CText::rotateDegreesAround_internal(float f, const Coord &p) {
	//pos = pos.rotateDegreesAround(f, p);
}



#endif

