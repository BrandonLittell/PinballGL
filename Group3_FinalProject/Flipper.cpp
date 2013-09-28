
#include "Flipper.h"


Flipper::Flipper( GLfloat initX, GLfloat initY, int numVerts, vec2* verts, vec3 color )
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

	maxRotation = M_PI/2.0f;
	defaultRotation = 0.0f;
	rotateDir = 0;
	rotating = false;
}


Flipper::~Flipper(void)
{
	delete [] mesh.color;
	delete [] mesh.vertices;
	delete [] mesh.transformedVertices;
}

void Flipper::update( float deltaTime )
{
	
	/*
	if( rotating )
	{
		transforms.rotate( rotateDir * maxRotation);// * deltaTime );
		if( transforms.getRotation() > maxRotation || transforms.getRotation() < -1*maxRotation )
		{
			rotateDir *= -1;
		}
	}
	*/
	mesh.calculateTransform( transforms.getMatrix() );
}

void Flipper::beginRotation( int key )
{
	//if( rotating == true ) return;

	//rotating = true;
	float temp = transforms.getRotation();
	switch( key )
	{
	case GLFW_KEY_LSHIFT:
		transforms.rotate( maxRotation );
		break;
	case GLFW_KEY_RSHIFT:
		transforms.rotate(  -maxRotation );
		break;
	}

	if( transforms.getRotation() < -maxRotation )
	{
		transforms.rotate( maxRotation );
	}
	else if( transforms.getRotation() > maxRotation )
	{
		transforms.rotate( -maxRotation );
	}

	mesh.calculateTransform( transforms.getMatrix() );
}