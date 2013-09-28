
#ifndef MESH_H
#define MESH_H

#include "includes.h"
#include "mat.h"

struct Mesh
{
	int numVertices;
	vec2* vertices;
	vec2* transformedVertices;
	vec3* color;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	const int getNumVertices() { return numVertices; }
	const vec2* getVertices() { return vertices; }

	const vec2 getFarthestPoint( vec2 direction )
	{
		if( numVertices <= 0 )
			return NULL;

		int farthestIndex = 0;
		float farthestDist = *transformedVertices * direction;
		float currDist;

		for( int i = 0; i < numVertices; ++i )
		{
			currDist = *( transformedVertices + i ) * direction;

			if( currDist > farthestDist )
			{
				farthestDist = currDist;
				farthestIndex = i;
			}
		}

		return *( transformedVertices + farthestIndex );
	}

	void calculateTransform( mat4 transMat )
	{
		
		float tempX;
		float tempY;

		for( int i = 0; i < numVertices; ++i )
		{
			tempX = transMat[0].x * ( vertices + i )->x +
				transMat[0].y * ( vertices + i )->y +
				transMat[0].z * 0 +
				transMat[0].w * 1;

			tempY = transMat[1].x * ( vertices + i )->x +
				transMat[1].y * ( vertices + i )->y +
				transMat[1].z * 0 +
				transMat[1].w * 1;

			*( transformedVertices + i ) = vec2( tempX, tempY );

		}
	}

};

#endif

