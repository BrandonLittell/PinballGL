
#include "Bumper.h"


Bumper::Bumper( GLfloat initX, GLfloat initY, int numVerts, vec2* verts, vec3 color )
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

Bumper::Bumper( GLfloat initX, GLfloat initY, int numVerts, int radius, vec3 color )
{
	mesh.numVertices = numVerts;
	mesh.vertices = new vec2[mesh.numVertices];
	mesh.color = new vec3[mesh.numVertices];
	mesh.transformedVertices = new vec2[mesh.numVertices];

	GLfloat theta = static_cast<GLfloat>( M_PI / 2 );
	for( int i = 0; i < numVerts; i++ )
	{
		theta += static_cast<GLfloat>( 2 * M_PI / numVerts );
		mesh.vertices[i] = vec2( radius * cos( theta ), radius * sin( theta ) );
		mesh.color[i] = vec3( color.x, color.y, color.z );
	}

	init();

	transforms.translate( vec2( initX, initY ) );

	mesh.calculateTransform( transforms.getMatrix() );
}


Bumper::~Bumper(void)
{
	delete [] mesh.color;
	delete [] mesh.vertices;
	delete [] mesh.transformedVertices;
}

void Bumper::update( float deltaTime )
{

}
