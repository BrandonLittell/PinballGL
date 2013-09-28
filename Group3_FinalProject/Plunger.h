
#ifndef PLUNGER_H
#define PLUNGER_H

#include "AbstractGameObject.h"

class Plunger : public AbstractGameObject
{
public:
	Plunger( GLfloat initX, GLfloat initY, 
		int numVerts, vec2* verts, 
		vec3 color );
	~Plunger(void);
	void update( float deltaTime );
};

#endif

