
#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "AbstractMenu.h"

class PauseMenu :
	public AbstractMenu
{
public:
	PauseMenu( HDC& ahDC, HGLRC& ahRC );
	~PauseMenu(void);
	void drawMenu( int selectedButton );
	State getNewState( int selectedButton );
};

#endif