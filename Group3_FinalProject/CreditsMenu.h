
#ifndef CREDITS_MENU_H
#define CREDITS_MENU_H

#include "AbstractMenu.h"

class CreditsMenu : public AbstractMenu
{
private:
	int numCreditsStrings;
	string* creditsText;
public:
	CreditsMenu( HDC& ahDC, HGLRC& ahRC );
	~CreditsMenu(void);
	void drawMenu( int selectedButton );
	State getNewState( int selectedButton );
};

#endif