
#include "HUD.h"


HUD::HUD( HDC& ahDC, HGLRC& ahRC ) : textWriter( ahDC, ahRC )
{
	titleString = "PINBALL";
	scoreString = "SCORE:";
	ballString = "BALLS: ";

	int numVerts = 4;
	vec2* bgVerts = new vec2[numVerts];

	bgVerts[0] = vec2(0.0, 0.0);
	bgVerts[1] = vec2(0.0, WINDOW_HEIGHT);
	bgVerts[2] = vec2(WINDOW_WIDTH/3, WINDOW_HEIGHT);
	bgVerts[3] = vec2(WINDOW_WIDTH/3, 0.0);

	bg = new DrawablePolygon(0.0f, 0.0f, numVerts, bgVerts, vec3( 0.9f, 0.9f, 0.9f ) );

	delete[] bgVerts;
	
}

HUD::~HUD(void)
{
	delete bg;
}


// draws the BG and text elements of the HUD
void HUD::draw( )
{
	char numberBuffer[21];
	GLfloat startX = WINDOW_WIDTH/13.0f;
	GLfloat startY = WINDOW_HEIGHT - WINDOW_HEIGHT/20.0f;
	bg->draw();
	textWriter.print( startX, startY - 1*WINDOW_HEIGHT/20.0f, titleString, vec3(0.0f, 0.0f, 0.0f) );
	textWriter.print( startX, startY - 2*WINDOW_HEIGHT/20.0f, scoreString, vec3(0.0f, 0.0f, 0.0f)  );
	// create a string for score
	sprintf(numberBuffer,"%i",score);
	textWriter.print( startX*2, startY - 3*WINDOW_HEIGHT/20.0f, numberBuffer, vec3(0.0f, 0.0f, 0.0f) );
	textWriter.print( startX, startY - 4*WINDOW_HEIGHT/20.0f, ballString, vec3(0.0f, 0.0f, 0.0f)  );
	// create a string for ballStock
	sprintf(numberBuffer,"%i",ballStock);
	textWriter.print( startX*2, startY - 5*WINDOW_HEIGHT/20.0f, numberBuffer, vec3(0.0f, 0.0f, 0.0f)  );
}
