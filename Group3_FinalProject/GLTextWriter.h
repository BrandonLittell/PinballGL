
#ifndef GL_TEXT_WRITER_H
#define GL_TEXT_WRITER_H

#include "includes.h"
#include <Windows.h>

//
//  BuildFont, KillFont, and glPrint from: http://nehe.gamedev.net/tutorial/bitmap_fonts/17002/
// http://www.mesa3d.org/brianp/sig97/gotchas.htm for help with resetting the rasterization
// http://stackoverflow.com/questions/6595772/painting-text-above-opengl-context-in-mfc for width of bitfont characters
// 

class GLTextWriter
{
private:
	HDC& hDC;
	HGLRC& hRC;
	GLuint base;
	ABC glyphInfo[256];
	GLYPHMETRICSFLOAT gmf[256];
	GLvoid BuildFont( GLvoid );
	GLvoid KillFont( GLvoid );
	GLvoid glPrint( const char* fmt );
	int stringWidth;
	GLfloat xPos;

public:
	GLTextWriter( HDC& ahDC, HGLRC& ahRC );
	~GLTextWriter( );
	void print( GLfloat x, GLfloat y, string text, vec3 color );
};

#endif