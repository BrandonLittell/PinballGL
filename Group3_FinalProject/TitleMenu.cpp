
#include "TitleMenu.h"


TitleMenu::TitleMenu( HDC& ahDC, HGLRC& ahRC ) : AbstractMenu( ahDC, ahRC )
{
	menuTitle = "PINBALL";
	numButtons = maxButtons;
	buttonStrings = new string[numButtons];
	buttonStrings[0] = "New game";
	buttonStrings[1] = "Instructions";
	buttonStrings[2] = "Credits";
	buttonStrings[3] = "Quit";
}


TitleMenu::~TitleMenu(void)
{
	// nothing to delete in this menu	
}

void TitleMenu::drawMenu( int selectedButton )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	bg->draw();

	// text
	textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT - WINDOW_HEIGHT/4, menuTitle, vec3( 0.0f, 0.0f, 0.0f ) );
	textWriter.print( WINDOW_WIDTH/4, WINDOW_HEIGHT - WINDOW_HEIGHT/3.3, "Eric Christenson", vec3( 0.0f, 0.0f, 0.0f ) );
	textWriter.print( WINDOW_WIDTH - WINDOW_WIDTH/4, WINDOW_HEIGHT - WINDOW_HEIGHT/3.3, "Brandon Littell", vec3( 0.0f, 0.0f, 0.0f ) );

	// buttons
	for ( int i = 0; i < numButtons; i++ )
	{
		buttonBG->changeColor( vec3( 0.0f, 0.0f, 0.0f ) );
		if( i == selectedButton )
		{	// change color of selected button
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

State TitleMenu::getNewState( int selectedButton )
{
	switch( selectedButton )
	{
	case 0:
		return NEW_GAME;
	case 1:
		return INSTRUCTIONS;
	case 2:
		return CREDITS;
	case 3:
		return QUIT;
	default:
		return NEW_GAME;
	}
}