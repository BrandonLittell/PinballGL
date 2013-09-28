
#ifndef TITLE_MENU_H
#define TITLE_MENU_H

#include "AbstractMenu.h"

class TitleMenu : public AbstractMenu
{
public:
	TitleMenu( HDC& ahDC, HGLRC& ahRC );
	~TitleMenu(void);
	void drawMenu( int selectedButton );
	State getNewState( int selectedButton );
};

#endif

