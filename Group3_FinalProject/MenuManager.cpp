
#include "MenuManager.h"


MenuManager::MenuManager( HDC& ahDC, HGLRC& ahRC ) 
{
	buttonIndex = 0;
	menus[TITLE] = new TitleMenu( ahDC, ahRC );
	menus[PAUSE] = new PauseMenu( ahDC, ahRC );
	menus[INSTRUCTIONS] = new InstructionsMenu( ahDC, ahRC );
	menus[CREDITS] = new CreditsMenu( ahDC, ahRC );
}

MenuManager::~MenuManager(void)
{
	// need to cast these or only AbstractMenu's dtor will get called
	delete static_cast<TitleMenu*>(menus[TITLE]);
	delete static_cast<PauseMenu*>(menus[PAUSE]);
	delete static_cast<InstructionsMenu*>(menus[INSTRUCTIONS]);
	delete static_cast<CreditsMenu*>(menus[CREDITS]);
}

void MenuManager::displayState( State stateToDraw )
{	// draw the specified menu with the current index
	menus[stateToDraw]->drawMenu( buttonIndex );
}

State MenuManager::handleMenuInput( int key, State currentState )
{
	// set final to current so no change in state if enter isn't pressed
	State finalState = currentState;
	switch( key )
	{
	case GLFW_KEY_ENTER:  // get the state corresponding to the index from the menu if enter is pressed
		finalState = menus[currentState]->getNewState( buttonIndex );
		break;
	case GLFW_KEY_UP:	// move the index up and check for loop
		buttonIndex--;
		if( buttonIndex < 0 ) buttonIndex = menus[currentState]->getNumButtons() - 1;
		break;
	case GLFW_KEY_DOWN:	// move the index down and check for loop
		buttonIndex++;
		if( buttonIndex == menus[currentState]->getNumButtons() ) buttonIndex = 0;
		break;
	default:
		break;
	}
	if( finalState != currentState ) buttonIndex = 0;
	return finalState;
 
}
