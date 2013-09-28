
#ifndef FLIPPER_H
#define FLIPPER_H

#include "AbstractGameObject.h"

class Flipper : public AbstractGameObject
{
private:
	GLfloat maxRotation;
	GLfloat defaultRotation;
	int rotateDir;
	bool rotating;
public:
	Flipper( GLfloat initX, GLfloat initY, int numVerts, vec2* verts, vec3 color );
	~Flipper(void);
	void update( float deltaTime );
	void beginRotation( int key );
};

#endif