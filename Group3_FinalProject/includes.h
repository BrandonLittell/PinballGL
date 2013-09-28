
#define _CRT_SECURE_NO_DEPRECATE
#include <GL/glew.h>
#include <GL/glfw.h>
#include <math.h>
#include <iostream>
#include "vec.h"

#ifdef _DEBUG
   #define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 750

#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

using namespace std;

#ifndef STATES
#define STATES
	enum State { TITLE, GAME, INSTRUCTIONS, CREDITS, PAUSE, QUIT, RETURN, NEW_GAME };
#endif