
#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "AbstractGameObject.h"
#include "Collision.h"
#include "Wall.h"
#include "HUD.h"
#include "Ball.h"
#include "MenuManager.h"
#include "Plunger.h"
#include "Spinner.h"
#include "Bumper.h"
#include "Flipper.h"
#include <list>
#include <vector>
#include <ctime>
#include <math.h>

#include <Windows.h>


using namespace std;

class Game
{
	
private:
	static const int STARTING_BALLS = 3;
	float deltaTime;
	list<Wall*> walls;
	Wall* ballKillerWall;  // remove balls from play if colliding with this
	Collision collision;
	HUD* hud;
	vector<Ball*> ballPool;
	vector<Ball*> activeBallList;
	vec2 ballSpawnPos, flipperPos, circleBumperPos;
	Plunger* plunger;
	Spinner* spinner;
	Bumper* circleBumper;
	Flipper* flipper;
	HDC hDC;
	HGLRC hRC;
	vector<State> stateStack;
	State currentState;
	MenuManager* menuManager;
	void displayGame();
	void updateGame( float deltaTime );
	int initWindow( GLFWkeyfun );
	
public:
	Game( GLFWkeyfun keyHandler );
	~Game( void );
	int runMainLoop();
	void initGame();
	void handleKeypress( int key, int press);
	
};

#endif

