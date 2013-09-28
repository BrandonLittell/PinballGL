
#ifndef SPINNER_H
#define SPINNER_H

#include "AbstractGameObject.h"

class Spinner : public AbstractGameObject
{
public:
	Spinner(GLfloat initX, GLfloat initY, 
		int numVerts, vec2* verts, 
		vec3 color );
	~Spinner(void);
	void update( float deltaTime );
};

#endif