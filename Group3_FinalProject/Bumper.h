
#ifndef BUMPER_H
#define BUMPER_H

#include "AbstractGameObject.h"

class Bumper : public AbstractGameObject
{
public:
	Bumper(GLfloat initX, GLfloat initY, 
		int numVerts, vec2* verts, 
		vec3 color );
	Bumper( GLfloat initX, GLfloat initY, int numVerts, int radius, vec3 color ); // for a circle bumper
	~Bumper(void);
	void update( float deltaTime );
};

#endif
