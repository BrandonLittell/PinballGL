
//  see
//  http://nehe.gamedev.net/tutorial/bitmap_fonts/17002/
//

#include "GLTextWriter.h"

GLTextWriter::GLTextWriter( HDC& ahDC, HGLRC& ahRC  ) : hDC( ahDC ), hRC( ahRC )
{	
	GLuint	PixelFormat;
	static PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		16,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	PixelFormat=ChoosePixelFormat(hDC,&pfd);
	SetPixelFormat(hDC,PixelFormat,&pfd);
	BuildFont();
	GetCharABCWidths( hDC, 0, 255, &glyphInfo[0] );
}

GLTextWriter::~GLTextWriter( )
{	
	KillFont();
}

void GLTextWriter::print( GLfloat x, GLfloat y, string text, vec3 color )
{
	
	// version 4.2.X on our personal computers vs 4.3.0 on the lab machines requires slightly different rasters
	static const GLubyte* ver = glGetString(GL_VERSION);
	const string verStr(reinterpret_cast<const char*>(ver));
	const string shortVerStr = verStr.substr(0,3);

	/*
	*    http://www.mesa3d.org/brianp/sig97/gotchas.htm Yay for Gotchas!
	*/
	glPushAttrib( GL_TRANSFORM_BIT | GL_VIEWPORT_BIT );

	/* Setup projection parameters */
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	//gluOrtho2D( 0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
		 
	// http://stackoverflow.com/questions/6595772/painting-text-above-opengl-context-in-mfc
	stringWidth=0; // pixels
	for(int j=0; j < text.length(); ++j )
		stringWidth += glyphInfo[ text.c_str()[j] ].abcA + glyphInfo[ text.c_str()[j] ].abcB + glyphInfo[ text.c_str()[j] ].abcC;

	glColor3f( color.x, color.y, color.z );
	/* set the raster (window) position */
	xPos = x - stringWidth/2.0f;
	glViewport( (int) xPos - 1, (int) y - 1, 2, 2 );
	if( !strcmp(shortVerStr.c_str(), "4.3") )
	{
		glRasterPos2f( xPos , y );
	}
	else
	{ // 4.2.X 
		glRasterPos2f( -1.0f + x/(WINDOW_WIDTH/2), -1.0f + y/(WINDOW_HEIGHT/2) );
	}

	glPrint( text.c_str() );

	/* restore matrices, viewport and matrix mode */
	glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
	glPopMatrix();
	glPopAttrib();


}

GLvoid GLTextWriter::BuildFont( GLvoid )
{
	HFONT font;
	HFONT oldfont;

	base = glGenLists(96);

	font = CreateFont(	-24,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject( hDC, font );
	wglUseFontBitmaps( hDC, 32, 96, base );
	SelectObject( hDC, font );
	DeleteObject(font);
}

GLvoid GLTextWriter::KillFont(GLvoid)									// Delete The Font
{
	glDeleteLists(base, 96);	
}

GLvoid GLTextWriter::glPrint( const char *fmt )					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}