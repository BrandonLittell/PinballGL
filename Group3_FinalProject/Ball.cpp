
#include "Ball.h"

Ball::Ball(GLfloat centerX, GLfloat centerY, GLfloat rad, int  numVerts, vec3 color)
{
	//center = vec2(centerX,centerY);
	radius = rad;
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

	//mesh.vertices[numVerts] = vec2( 0.0f, 0.0f );
	//mesh.color[numVerts] = color;
	
	init();

	transforms.translate( vec2( centerX, centerY ) );

	mesh.calculateTransform( transforms.getMatrix() );
}


Ball::~Ball( void )
{
	delete [] mesh.vertices;
	delete [] mesh.color;
	delete [] mesh.transformedVertices;
}

void Ball::update( float deltaTime )
{
	rigidBody.update( deltaTime );

	mesh.calculateTransform( transforms.getMatrix() );
}

void Ball::reset()
{
	rigidBody.reset();
	rigidBody.setLinearVelocity( vec2( 0.0f, 15.0f ) );
}
