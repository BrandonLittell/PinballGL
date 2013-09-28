
#include "PauseMenu.h"


PauseMenu::PauseMenu( HDC& ahDC, HGLRC& ahRC ) : AbstractMenu( ahDC, ahRC )
{
	menuTitle = "PAUSE";
	numButtons = maxButtons;
	buttonStrings = new string[numButtons];
	buttonStrings[0] = "Return";
	buttonStrings[1] = "Instructions";
	buttonStrings[2] = "New Game";
	buttonStrings[3] = "Main";
}


PauseMenu::~PauseMenu(void)
{
	// nothing to delete in this menu
}

void PauseMenu::drawMenu( int selectedButton )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	bg->draw();

	textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT - WINDOW_HEIGHT/4, menuTitle, vec3( 0.0f, 0.0f, 0.0f ) );

	// draw buttons
	for ( int i = 0; i < numButtons; i++ )
	{
		buttonBG->changeColor( vec3( 0.0f, 0.0f, 0.0f ) );
		if( i == selectedButton )
		{	// change color and move pointer
			pointer->transforms.moveTo( vec2( WINDOW_WIDTH/4 , WINDOW_HEIGHT/2 - i*(WINDOW_HEIGHT/8) ) );
			pointer->draw();
			buttonBG->changeColor( vec3( 0.0f, -1.0f, -1.0f ) );
		}
		buttonBG->transforms.moveTo( vec2( WINDOW_WIDTH/2 , WINDOW_HEIGHT/2 - i*(WINDOW_HEIGHT/8) ) );
		buttonBG->draw();
		textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - i*(WINDOW_HEIGHT/8) - 6, buttonStrings[i], vec3(0.0f, 0.0f, 0.0f) );
	}
	
	glfwSwapBuffers();
}

State PauseMenu::getNewState( int selectedButton )
{
	switch( selectedButton )
	{
	case 0:
		return RETURN;
	case 1:
		return INSTRUCTIONS;
	case 2:
		return NEW_GAME;
	case 3:
		return TITLE;
	default:
		return NEW_GAME;
	}
}