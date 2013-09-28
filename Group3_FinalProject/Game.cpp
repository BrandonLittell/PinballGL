

#include "Game.h"


Game::Game( GLFWkeyfun keyHandler )
{

    initWindow( keyHandler );

    currentState = TITLE;
    stateStack.push_back( currentState );

	menuManager = new MenuManager( hDC, hRC );
	hud = new HUD( hDC, hRC );
	for(int i = 0; i < STARTING_BALLS; i++ ) 
		ballPool.push_back( new Ball(  0.0f, 0.0f, WINDOW_WIDTH/110, 16, vec3(1.0f, 0.0f, 0.0f) ) );
		
	ballSpawnPos = vec2( WINDOW_WIDTH - WINDOW_WIDTH/20 - WINDOW_WIDTH/90, WINDOW_HEIGHT/8 );

    vec2* verts = new vec2[4];

 #pragma region DO NOT OPEN - WALLS

	GLfloat left = WINDOW_WIDTH/3+WINDOW_WIDTH/20;
	GLfloat right = WINDOW_WIDTH-WINDOW_WIDTH/20;
	//surrounding walls
	verts[0] = vec2( -WINDOW_WIDTH/40, -WINDOW_HEIGHT/2 );
	verts[1] = vec2( verts[0].x, verts[0].y + WINDOW_HEIGHT );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/20, verts[0].y + WINDOW_HEIGHT );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/20, verts[0].y );
	walls.push_front( new Wall(WINDOW_WIDTH/3 + WINDOW_WIDTH/40, WINDOW_HEIGHT/2, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	walls.push_front( new Wall(WINDOW_WIDTH - WINDOW_WIDTH/40, WINDOW_HEIGHT/2, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	verts[0] = vec2( -WINDOW_WIDTH/6.0f, -WINDOW_HEIGHT/6 - WINDOW_HEIGHT/6 );
	verts[1] = vec2( verts[0].x, verts[0].y + WINDOW_HEIGHT/3 + WINDOW_HEIGHT/6);
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/3.0f, verts[0].y + WINDOW_HEIGHT/3 + WINDOW_HEIGHT/6 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/3.0f, verts[0].y + WINDOW_HEIGHT/6);
	walls.push_front( new Wall(WINDOW_WIDTH - WINDOW_WIDTH/3 - WINDOW_WIDTH/6.0f, WINDOW_HEIGHT - WINDOW_HEIGHT/6, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	verts[0] = vec2( -WINDOW_WIDTH/6.0f, -WINDOW_HEIGHT/6 );
	verts[1] = vec2( verts[0].x, verts[0].y + WINDOW_HEIGHT/3 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/3.0f, verts[0].y + WINDOW_HEIGHT/3 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/3.0f, verts[0].y - WINDOW_HEIGHT/6 );
	walls.push_front( new Wall(WINDOW_WIDTH - WINDOW_WIDTH/3 + WINDOW_WIDTH/6.0f, WINDOW_HEIGHT - WINDOW_HEIGHT/6, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	verts[0] = vec2( -WINDOW_WIDTH/3.0f,- WINDOW_HEIGHT/40 );
	verts[1] = vec2( verts[0].x, verts[0].y + WINDOW_HEIGHT/20 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/1.5f, verts[0].y + WINDOW_HEIGHT/20 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/1.5f, verts[0].y );
	ballKillerWall = new Wall(WINDOW_WIDTH - WINDOW_WIDTH/3, WINDOW_HEIGHT/40, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) );
	
	// lower left corner
	verts[0] = vec2( -WINDOW_WIDTH/10              , -WINDOW_HEIGHT/20 );
	verts[1] = vec2( verts[0].x                    , verts[0].y + WINDOW_HEIGHT/7 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/5   , verts[0].y + WINDOW_HEIGHT/15 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/5   , verts[0].y );
	walls.push_front( new Wall(WINDOW_WIDTH/3 + WINDOW_WIDTH/10 + WINDOW_WIDTH/20, WINDOW_HEIGHT/10, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	
	// lower right corner
	verts[0] = vec2( -WINDOW_WIDTH/10              , -WINDOW_HEIGHT/20 );
	verts[1] = vec2( verts[0].x                    , verts[0].y + WINDOW_HEIGHT/15 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/5   , verts[0].y + WINDOW_HEIGHT/7 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/5   , verts[0].y );
	walls.push_front( new Wall(WINDOW_WIDTH - WINDOW_WIDTH/5, WINDOW_HEIGHT/10, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	
	// chute wall
	verts[0] = vec2( -WINDOW_WIDTH/70    , -WINDOW_HEIGHT/5.5f );
	verts[1] = vec2( verts[0].x					       , verts[0].y + WINDOW_HEIGHT/2.75f );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/35      , verts[0].y + WINDOW_HEIGHT/2.75f );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/35      , verts[0].y );
	walls.push_front( new Wall(WINDOW_WIDTH - WINDOW_WIDTH/10 + WINDOW_WIDTH/70, WINDOW_HEIGHT/5.5f + WINDOW_HEIGHT/20, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	
	// slanted wall above chute
	verts[0] = vec2( 0.0f, -WINDOW_HEIGHT/8 );
	verts[1] = vec2( verts[0].x - WINDOW_WIDTH/10, verts[0].y + WINDOW_HEIGHT/4 );
	verts[2] = vec2( verts[0].x, verts[0].y + WINDOW_HEIGHT/4 );
	verts[3] = vec2( verts[0].x + 1, verts[0].y + 1 );
	walls.push_front( new Wall( WINDOW_WIDTH - WINDOW_WIDTH/40, WINDOW_HEIGHT/2 + WINDOW_WIDTH/24, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	
	// left flipper 
	verts[0] = vec2( -WINDOW_WIDTH/80, -WINDOW_HEIGHT/30 );
	verts[1] = vec2( verts[0].x                      , verts[0].y + WINDOW_HEIGHT/15 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/40    , verts[0].y + WINDOW_HEIGHT/15 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/40    , verts[0].y);
	walls.push_front( new Wall(WINDOW_WIDTH/3 + WINDOW_WIDTH/12 + WINDOW_WIDTH/80, WINDOW_HEIGHT/4.4f + WINDOW_HEIGHT/30, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	verts[0] = vec2( -WINDOW_WIDTH/14, WINDOW_HEIGHT/31 );
	verts[1] = vec2( verts[0].x + WINDOW_WIDTH/40    , verts[0].y );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/7     , verts[0].y - WINDOW_HEIGHT/19 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/7     , verts[0].y - WINDOW_HEIGHT/15.5f );
	walls.push_front( new Wall(WINDOW_WIDTH/3 + WINDOW_WIDTH/12 + WINDOW_WIDTH/14, WINDOW_HEIGHT/4.4f - WINDOW_HEIGHT/31, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	
	// right flipper wall
	verts[0] = vec2( -WINDOW_WIDTH/80, -WINDOW_HEIGHT/30 );
	verts[1] = vec2( verts[0].x                        , verts[0].y + WINDOW_HEIGHT/15 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/40      , verts[0].y + WINDOW_HEIGHT/15 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/40      , verts[0].y );
	walls.push_front( new Wall(WINDOW_WIDTH - WINDOW_WIDTH/7.49f - WINDOW_WIDTH/80, WINDOW_HEIGHT/30 + WINDOW_HEIGHT/4.4f, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	verts[0] = vec2( WINDOW_WIDTH/14, WINDOW_HEIGHT/31 );
	verts[1] = vec2( verts[0].x - WINDOW_WIDTH/7     , verts[0].y - WINDOW_HEIGHT/15.5f );
	verts[2] = vec2( verts[0].x - WINDOW_WIDTH/7     , verts[0].y - WINDOW_HEIGHT/19 );
	verts[3] = vec2( verts[0].x - WINDOW_WIDTH/40    , verts[0].y );
	walls.push_front( new Wall(WINDOW_WIDTH - WINDOW_WIDTH/7.49f - WINDOW_WIDTH/14, WINDOW_HEIGHT/4.4f - WINDOW_HEIGHT/31, 4, verts, vec3( 1.0f, 1.0f, 1.0f ) ) );
	

#pragma endregion DO NOT OPEN - WALLS

	// the circle bumper
	circleBumperPos = vec2( WINDOW_WIDTH - WINDOW_WIDTH/2.3f, WINDOW_HEIGHT/2.5 );
	circleBumper = new Bumper( circleBumperPos.x, circleBumperPos.y, 16, WINDOW_HEIGHT/20, vec3( 0.0f, 1.0f, 0.0f ) );
	
	// plunger
	verts[0] = vec2( -WINDOW_WIDTH/90    , 0.0f );
	verts[1] = vec2( verts[0].x					       , verts[0].y + WINDOW_HEIGHT/16 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/45      , verts[0].y + WINDOW_HEIGHT/16 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/45      , verts[0].y );
	plunger = new Plunger(WINDOW_WIDTH - WINDOW_WIDTH/20 - WINDOW_WIDTH/90, WINDOW_HEIGHT/20, 4 ,verts ,vec3( 0.0f, 0.0f, 1.0f ) );

	// the spinner
	verts[0] = vec2( -WINDOW_WIDTH/110    , -WINDOW_HEIGHT/16 );
	verts[1] = vec2( verts[0].x					       , verts[0].y + WINDOW_HEIGHT/8 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/55      , verts[0].y + WINDOW_HEIGHT/8 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/55      , verts[0].y );
	spinner = new Spinner(WINDOW_WIDTH - WINDOW_WIDTH/4, WINDOW_HEIGHT/3, 4, verts, vec3( 0.0f, 0.0f, 1.0f ) );

	// the flipper
	verts[0] = vec2( -WINDOW_WIDTH/120, 0.0f );
	verts[1] = vec2( verts[0].x + WINDOW_WIDTH/280, verts[0].y + WINDOW_HEIGHT/20 );
	verts[2] = vec2( verts[0].x + WINDOW_WIDTH/60.0f - WINDOW_WIDTH/280, verts[0].y + WINDOW_HEIGHT/20 );
	verts[3] = vec2( verts[0].x + WINDOW_WIDTH/60.0f, verts[0].y  );
	flipperPos = vec2( WINDOW_WIDTH - WINDOW_WIDTH/3 - WINDOW_WIDTH/40, WINDOW_HEIGHT/6.8f );
	flipper = new Flipper( flipperPos.x, flipperPos.y, 4, verts, vec3( 0.0f, 0.5f, 0.5f ) );
	delete [] verts;

}


Game::~Game( void )
{

	// deleting walls
	for( auto it = walls.begin(); it != walls.end(); it++ )
	{
		delete *it;
	}
	delete ballKillerWall;
	// deleting balls
	for( auto poolIt = ballPool.begin(); poolIt != ballPool.end(); poolIt++ )
	{
		delete *poolIt;
	}
	for( auto ballIt = activeBallList.begin(); ballIt != activeBallList.end(); ballIt++ )
	{
		delete *ballIt;
	}
	delete hud;
	delete menuManager;
	delete plunger;
	delete spinner;
	delete circleBumper;
	delete flipper;
	
}

int Game::runMainLoop( void )
{
    // DeltaTime help from Colden
    clock_t prevTime = clock();
    clock_t currTime = clock();

    float totalTime = 0.0f;
    int totalFrames = 0;
	float updateTimer = 0.0f;
	const float updateDelay = 1.0/1000.0f;

    /* Loop until the user closes the window */
    while ( glfwGetWindowParam( GLFW_OPENED ) )
    {
        prevTime = currTime;
        currTime = clock();

        deltaTime = static_cast<float>( currTime - prevTime ) / CLOCKS_PER_SEC;

#ifdef _DEBUG
        totalTime += deltaTime;
        ++totalFrames;

        if( totalTime >= 1.0f )
        {
            cout << totalFrames << endl;
            totalTime = 0.0f;
            totalFrames = 0;
        }
#endif
		updateTimer += deltaTime;
		if( updateTimer > updateDelay )
		{
			
			if( currentState != stateStack.back() )
			{
				if( currentState == RETURN )
				{
					stateStack.pop_back();
					currentState = stateStack.back();
				}
				else if( currentState == QUIT )
				{
					glfwTerminate();
				}
				else if( currentState != NEW_GAME )
				{
					stateStack.push_back( currentState );
				}
			}
		
			// game over condition
			if( currentState == GAME && activeBallList.size() == 0 && hud->ballStock == 0 )
			{
				currentState = CREDITS;
			}
			
			switch( currentState )
			{
			case PAUSE:
			case INSTRUCTIONS:
			case CREDITS:
			case TITLE:
				menuManager->displayState( currentState );
				break;
			case NEW_GAME:
				initGame();
				break;
			case GAME:
				updateGame( updateDelay );
				displayGame();
				break;
			default:
				break;

			};

			updateTimer = 0.0f;
		}
    }

    return 0;
}

void Game::initGame()
{
	// move any active balls to the ballQueue
	for( auto ballIt = activeBallList.begin(); ballIt != activeBallList.end();  )
	{
			ballPool.push_back( *ballIt );
			ballIt = activeBallList.erase( ballIt );
	}
	flipper->transforms.init();
	flipper->transforms.translate( flipperPos );
	circleBumper->transforms.init();
	circleBumper->transforms.translate( circleBumperPos );
	stateStack.clear();
	currentState = GAME;
	stateStack.push_back(currentState);
	hud->score = 0;
	hud->ballStock = STARTING_BALLS;

}

void Game::displayGame( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	hud->draw();
	auto wallItEnd = walls.end();
	for( auto it = walls.begin(); it != wallItEnd; it++ )
	{
		(*it)->draw();
	}
	ballKillerWall->draw();
	plunger->draw();
	spinner->draw();
	circleBumper->draw();
	auto ballItEnd = activeBallList.end();
	for( auto ballIt = activeBallList.begin(); ballIt != ballItEnd; ballIt++ )
	{
		(*ballIt)->draw();
	}
	flipper->draw();

	glfwSwapBuffers();

}

int Game::initWindow( GLFWkeyfun keyHandler )
{
        
    /* Initialize the library */
    if ( !glfwInit() )
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    if ( !glfwOpenWindow( WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 0, 24, 0, GLFW_WINDOW ) )
        return -1;

    glewExperimental = GL_TRUE; 
    glewInit();

    glfwSetWindowTitle( "SUPER MEGA ULTIMATE DSA PINBALL S2 EXTREME EXTENDED ANNIVERSARY EDITION" );

    // function to handle keypresses
    glfwSetKeyCallback( keyHandler );
        
    HWND hwnd = GetForegroundWindow();
    hDC = GetDC( hwnd );
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC,hRC);

    return 0;
}

void Game::updateGame( float deltaTime )
{
	// update objects that move
	plunger->update( deltaTime );
	spinner->update( deltaTime );
	circleBumper->update( deltaTime );
	flipper->update( deltaTime );

	// Collision Detection and response!

	// To remove elements in a vector while using the iterator:
	// http://stackoverflow.com/questions/991335/how-to-erase-delete-pointers-to-objects-stored-in-a-vector
	for( auto ballIt = activeBallList.begin(); ballIt != activeBallList.end();  )
	{
		(*ballIt)->update( deltaTime );

		// Shammy the Killer Wall
		if( collision.checkCollision( (*ballIt), ballKillerWall ) )
		{	// remove ball from play
			ballPool.push_back( *ballIt );
			ballIt = activeBallList.erase( ballIt );
		}
		else
		{
			// Wall collision
			for( auto i = walls.begin(); i != walls.end(); i++ )
			{
				if( collision.checkCollision( (*ballIt), *i ) )
				{
					(*ballIt)->rigidBody.collisionResponse( 
                                        collision.getCollisionDepth(),
                                        collision.getCollisionNormal(),
										&(*i)->rigidBody );
				}
			}

			// Spinner collision
			if( collision.checkCollision( (*ballIt), spinner ) )
			{
					(*ballIt)->rigidBody.collisionResponse( 
                                        collision.getCollisionDepth(),
                                        collision.getCollisionNormal(),
										&spinner->rigidBody );
					hud->score += 10;
			}

			// Plunger collision
			if( collision.checkCollision( (*ballIt), plunger ) )
					(*ballIt)->rigidBody.collisionResponse( 
                                        collision.getCollisionDepth(),
                                        collision.getCollisionNormal(),
										&plunger->rigidBody );

			
			// bumper collision
			if( collision.checkCollision( (*ballIt), circleBumper ) )
			{
					(*ballIt)->rigidBody.collisionResponse( 
                                        collision.getCollisionDepth(),
                                        collision.getCollisionNormal(),
										&circleBumper->rigidBody );
					circleBumper->transforms.shear( vec2( 0.02f, 0.02f ) );
					circleBumper->mesh.calculateTransform( circleBumper->transforms.getMatrix() );

					hud->score += 10;
			}

			// Flipper collision
			if( collision.checkCollision( (*ballIt), flipper ) )
			{
					(*ballIt)->rigidBody.collisionResponse( 
                                        collision.getCollisionDepth(),
                                        collision.getCollisionNormal(),
										&flipper->rigidBody );
					flipper->transforms.scale( 0.9f );
			}

			++ballIt;  // increment if 
		}
	}
	

}

void Game::handleKeypress( int key, int press )
{

	switch( currentState )
	{
	case TITLE:
	case INSTRUCTIONS:
	case CREDITS:
	case PAUSE:
		if ( press )
		{
			currentState = menuManager->handleMenuInput( key, currentState );
		}
		break;
	case GAME:
		switch ( key )
		{
		case GLFW_KEY_SPACE:
			if ( press && hud->ballStock != 0 && ballPool.size() != 0 )
			{
				activeBallList.push_back( ballPool.back() );
				activeBallList.back()->reset();
				activeBallList.back()->transforms.moveTo( ballSpawnPos );
				ballPool.pop_back();
				hud->ballStock--;
			}
			break;
		case GLFW_KEY_ESC:
			currentState = PAUSE;
			break;
		case GLFW_KEY_LSHIFT:
		case GLFW_KEY_RSHIFT:
			if ( press ) flipper->beginRotation( key );
			break;
		default:
			break;
		}
		break;
	case QUIT:
		break;
	default:
		break;
	};

}

