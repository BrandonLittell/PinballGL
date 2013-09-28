
#include "Wall.h"


Wall::Wall( GLfloat initX, GLfloat initY, int numVerts, vec2* verts, vec3 color )
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

	rigidBody.mass = 4000;

	transforms.translate( vec2( initX, initY ) );
	
	mesh.calculateTransform( transforms.getMatrix() );

}


Wall::~Wall( void )
{
	delete [] mesh.color;
	delete [] mesh.vertices;
	delete [] mesh.transformedVertices;
}


void Wall::update( float deltaTime )
{

}
