#include "AbstractMenu.h"


AbstractMenu::AbstractMenu( HDC& ahDC, HGLRC& ahRC ) : textWriter( ahDC, ahRC )
{

	int numVerts = 4;
	vec2* verts = new vec2[numVerts];

	// set up the BG
	verts[0] = vec2(0.0, 0.0);
	verts[1] = vec2(0.0, WINDOW_HEIGHT);
	verts[2] = vec2(WINDOW_WIDTH, WINDOW_HEIGHT);
	verts[3] = vec2(WINDOW_WIDTH, 0.0);
	bg = new DrawablePolygon(0.0f, 0.0f, numVerts, verts, vec3( 0.0f, 0.4f, 0.6f ) );
	
	// set up the buttonBG
	verts[0] = vec2( -WINDOW_WIDTH/6            , -WINDOW_HEIGHT/24 );
	verts[1] = vec2( verts[0].x                 , verts[0].y + WINDOW_HEIGHT/12 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/3, verts[0].y + WINDOW_HEIGHT/12 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/3, verts[0].y );
	buttonBG = new DrawablePolygon( 0.0f, 0.0f, numVerts, verts, vec3( 1.0f, 1.0f, 1.0f ) ) ;
	delete[] verts;

	// set up the pointer
	numVerts = 3;
	vec2* verts3 = new vec2[numVerts];
	verts3[0] = vec2( -WINDOW_WIDTH/20, -WINDOW_HEIGHT/40 );
	verts3[1] = vec2( -WINDOW_WIDTH/20, WINDOW_HEIGHT/40 );
	verts3[2] = vec2( 0.0f, 0.0f );
	pointer = new DrawablePolygon( 100.0f, 400.0f, numVerts, verts3, vec3( 1.0f, 0.0f, 0.0f ) );
	delete [] verts3;

}


AbstractMenu::~AbstractMenu(void)
{
	delete bg;
	delete buttonBG;
	delete [] buttonStrings;
	delete pointer;
}

