
/***************
* Eric Christenson, Brandon Littell
* DSA Final Project - SUPER MEGA ULTIMATE DSA PINBALL S2 EXREME EXTENDED ANNIVERSARY EDITION
*
****************/

#pragma comment ( lib, "GLFW.lib" )
#pragma comment ( lib, "GLFWDLL.lib" )
#pragma comment ( lib, "glew32.lib" )
#pragma comment ( lib, "OpenGL32.lib" )

#include "Game.h"





void GLFWCALL handleKeypress( int key, int press);
void test();
Game* pinball; 

void main()
{
	test();
	_CrtDumpMemoryLeaks();
}

void test()
{
	pinball = new Game( handleKeypress );
	pinball->runMainLoop();
	delete pinball;
}

void GLFWCALL handleKeypress( int key, int press )
{
	pinball->handleKeypress( key, press );
}