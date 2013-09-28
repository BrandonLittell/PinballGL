
#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "DrawablePolygon.h"
#include "GLTextWriter.h"
#include "includes.h"
#include "TitleMenu.h"
#include "PauseMenu.h"
#include "InstructionsMenu.h"
#include "CreditsMenu.h"
#include <map>

class MenuManager
{
private:
	map<State, AbstractMenu*> menus;
	int buttonIndex;
public:
	MenuManager( HDC& ahDC, HGLRC& ahRC );
	~MenuManager(void);
	void displayState( State stateToDraw );
	State handleMenuInput( int key, State currentState );
};

#endif