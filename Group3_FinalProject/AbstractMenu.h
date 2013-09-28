
#ifndef ABSTRACT_MENU_H
#define ABSTRACT_MENU_H

#include "DrawablePolygon.h"
#include "GLTextWriter.h"
#include "includes.h"

class AbstractMenu
{
protected:
	static const int maxButtons = 4;
	string menuTitle;
	int numButtons;
	string* buttonStrings;
	DrawablePolygon* bg;
	DrawablePolygon* buttonBG;
	DrawablePolygon* pointer;
	GLTextWriter textWriter;
	AbstractMenu( HDC& ahDC, HGLRC& ahRC );

public:
	~AbstractMenu(void);
	virtual void drawMenu( int selectedButton ) = 0;
	virtual State getNewState( int selectedButton ) = 0;
	int getNumButtons() { return numButtons; }
};

#endif