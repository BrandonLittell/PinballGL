#include "InstructionsMenu.h"


InstructionsMenu::InstructionsMenu(  HDC& ahDC, HGLRC& ahRC ) : AbstractMenu( ahDC, ahRC )
{
	menuTitle = "INSTRUCTIONS";
	numButtons = 1;
	buttonStrings = new string[numButtons];
	buttonStrings[0] = "Return";

	numInstructionStrings = 5;
	instructionText = new string[numInstructionStrings];
	instructionText[0] = "Press SPACE to launch a ball.";
	instructionText[1] = "Press L/R Shift to rotate the flipper L/R.";
	instructionText[2] = "When you run out of active and stocked balls";
	instructionText[3] = "the game is over.";
	instructionText[4] = "Good Luck!";
}


InstructionsMenu::~InstructionsMenu(void)
{
	delete [] instructionText;
	
}

void InstructionsMenu::drawMenu( int selectedButton )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	bg->draw();

	textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT - WINDOW_HEIGHT/4, menuTitle, vec3( 0.0f, 0.0f, 0.0f ) );
	
	// draw the instructions
	for( int i = 0; i < numInstructionStrings; i++ )
	{
		textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT - WINDOW_HEIGHT/4 - (i + 1)*(WINDOW_HEIGHT/16), instructionText[i], vec3( 0.0f, 0.0f, 0.0f ) );
	}
	
	// only a single button to draw in this menu
	pointer->transforms.moveTo( vec2( WINDOW_WIDTH/4 , WINDOW_HEIGHT/2 - (maxButtons - 1)*(WINDOW_HEIGHT/8) ) );
	pointer->draw();
	
	buttonBG->changeColor( vec3( 0.0f, -1.0f, -1.0f ) );
	buttonBG->transforms.moveTo( vec2( WINDOW_WIDTH/2 , WINDOW_HEIGHT/2 - (maxButtons - 1)*(WINDOW_HEIGHT/8) ) );
	buttonBG->draw();
	textWriter.print( WINDOW_WIDTH/2, WINDOW_HEIGHT/2 -  (maxButtons - 1 )*(WINDOW_HEIGHT/8) - 6, buttonStrings[0], vec3(0.0f, 0.0f, 0.0f) );
	
	
	glfwSwapBuffers();
}

State InstructionsMenu::getNewState( int selectedButton )
{
	switch ( selectedButton )
	{
	case 0:
		return RETURN;
	default:
		return NEW_GAME;
	}
}