
#include "Plunger.h"


Plunger::Plunger( GLfloat initX, GLfloat initY, int numVerts, vec2* verts, vec3 color )
{
	mesh.numVertices = numVerts;
	mesh.vertices = new vec2[numVerts];
	mesh.color = new vec3[numVerts];
	mesh.transformedVertices = new vec2[mesh.numVertices];
	
	for( int i = 0; i < numVerts; i++ )
	{
		mesh.vertices[i] = verts[i];
		mesh.color[i] = color;
	}

	init();
	transforms.translate( vec2( initX, initY ) );

	mesh.calculateTransform( transforms.getMatrix() );
}


Plunger::~Plunger(void)
{
	delete [] mesh.color;
	delete [] mesh.vertices;
	delete [] mesh.transformedVertices;
}

void Plunger::update( float deltaTime )
{
//	transforms.scale( vec2( 1.0f, 1.01f * deltaTime ) );
//	mesh.calculateTransform( transforms.getMatrix() );
}
