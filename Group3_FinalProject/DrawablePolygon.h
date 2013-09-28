
#ifndef DRAWABLE_POLYGON_H
#define DRAWABLE_POLYGON_H

#include "includes.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"

class DrawablePolygon
{
private:
	Mesh mesh;
	static Shader shader;
	vec3 deltaColor;
public:
	Transform transforms;
	DrawablePolygon( GLfloat initX, GLfloat initY, int numVerts, vec2* verts, vec3 color );
	~DrawablePolygon();
	void init( void );
	void draw( void );
	void changeColor( vec3 dColor );

};

#endif