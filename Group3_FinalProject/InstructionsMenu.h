
#ifndef INSTRUCTIONS_MENU_H
#define INSTRUCTIONS_MENU_H

#include "AbstractMenu.h"

class InstructionsMenu : public AbstractMenu
{
private:
	int numInstructionStrings;
	string* instructionText;
public:
	InstructionsMenu(  HDC& ahDC, HGLRC& ahRC );
	~InstructionsMenu(void);
	void drawMenu( int selectedButton );
	State getNewState( int selectedButton );
};

#endif

