
#ifndef BALL_H
#define BALL_H

#include "AbstractGameObject.h"

class Ball : public AbstractGameObject
{
private:
	GLfloat radius;
public:
	Ball( GLfloat centerX, GLfloat centerY, GLfloat rad, int  numVerts, vec3 color );
	~Ball(void);
	//void init( void );
	void update( float deltaTime );
	void reset();
};

#endif
