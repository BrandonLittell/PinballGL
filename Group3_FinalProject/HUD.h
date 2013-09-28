
#ifndef HUD_H
#define HUD_H

#include "DrawablePolygon.h"
#include "GLTextWriter.h"

class HUD
{
private:
	string titleString;
	string scoreString;
	string ballString;
	DrawablePolygon* bg;
	GLTextWriter textWriter;

public:
	int score;
	int ballStock;
	HUD( HDC&, HGLRC& );
	~HUD(void);
	void draw( void );
};

#endif