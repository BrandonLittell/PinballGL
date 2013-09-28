
#ifndef WALL_H
#define WALL_H

#include "AbstractGameObject.h"

class Wall : public AbstractGameObject
{
public:
	Wall( GLfloat initX, GLfloat initY, 
		int numVerts, vec2* verts, 
		vec3 color );
	~Wall( void );
	void update( float deltaTime );

};

#endif
