
#include "CreditsMenu.h"


CreditsMenu::CreditsMenu( HDC& ahDC, HGLRC& ahRC ) : AbstractMenu( ahDC, ahRC ) 
{
	menuTitle = "CREDITS";
	numButtons = 2;
	buttonStrings = new string[numButtons];
	buttonStrings[0] = "New Game";
	buttonStrings[1] = "Title";

	numCreditsStrings = 7;
	creditsText = new string[numCreditsStrings];
	creditsText[0] = "nehe.gamedev.net/tutorial/bitmap_fonts/17002/";

	creditsText[1] = "www.opengl-tutorial.org/beginners-tutorials/";
	creditsText[2] = "tutorial-4-a-colored-cube/";

	creditsText[3] = "www.mesa3d.org/brianp/sig97/gotchas.htm";
	creditsText[4] = "stackoverflow.com/questions/6595772/";
	creditsText[5] = "painting-text-above-opengl-context-in-mfc";
	creditsText[6] = "www.codezealot.org";
}


CreditsMenu::~CreditsMenu(void)
{	
	delete [] creditsText;
}

void CreditsMenu::drawMenu( int selectedButton )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	bg->draw();

	textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT - WINDOW_HEIGHT/6, menuTitle, vec3( 0.0f, 0.0f, 0.0f ) );
	
	// draw all the credits
	for( int i = 0; i < numCreditsStrings; i++ )
	{
		textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT - WINDOW_HEIGHT/6 - (i + 1)*(WINDOW_HEIGHT/16), creditsText[i], vec3( 0.0f, 0.0f, 0.0f ) );
	}

	// draw buttons 
	for( int j = 0; j < numButtons; j++ )
	{
		buttonBG->changeColor( vec3( 0.0f, 0.0f, 0.0f ) );
		if( j == selectedButton )
		{ // place the pointer
			pointer->transforms.moveTo( vec2( WINDOW_WIDTH/4 , WINDOW_HEIGHT/2 - (j + numButtons)*(WINDOW_HEIGHT/8)  ) );
			pointer->draw();
			buttonBG->changeColor( vec3( 0.0f, -1.0f, -1.0f ) );
		}
		buttonBG->transforms.moveTo( vec2( WINDOW_WIDTH/2 , WINDOW_HEIGHT/2 - (j + numButtons)*(WINDOW_HEIGHT/8) ) );
		buttonBG->draw();
		textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - (j + numButtons)*(WINDOW_HEIGHT/8) - 6, buttonStrings[j], vec3(0.0f, 0.0f, 0.0f) );
	}


	glfwSwapBuffers();
}

State CreditsMenu::getNewState( int selectedButton )
{
	switch( selectedButton )
	{
	case 0:
		return NEW_GAME;
	case 1:
		return TITLE;
	default:
		return NEW_GAME;
	}
}