
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec.h"
#include "mat.h"
#include <math.h>

struct Transform
{
private:
	vec2 pos;
	vec2 scaleVector;
	vec2 shearVector;
	GLfloat rotation;
	mat4 matrix;
public:
	float getRotation() { return rotation; }

	void init()
	{
		// reset all values
		rotation = 0.0f;
		pos = vec2( 0.0f, 0.0f );
		scaleVector = vec2( 0.0f, 0.0f );
		shearVector = vec2( 0.0f, 0.0f );
		matrix = mat4();
	}

	void translate( const vec2& offset )
	{
		// Add offset
		matrix[0].w += offset.x;
		matrix[1].w += offset.y;

		// Update position
		pos += offset;
	}

	void moveTo( const vec2& newPos )
	{ // To arbitrarily move an object to a new location
		// Add offset
		matrix[0].w = newPos.x;
		matrix[1].w = newPos.y;

		// Update position
		pos = vec2( newPos.x, newPos.y );
	}

	void rotate( float angle )
	{
		// Build a new matrix for calculation
		mat4 rotateMat;

		// This matrix is for rotation around a z axis
		rotateMat[0].x = cos( angle );
		rotateMat[0].y = -sin( angle );
		rotateMat[1].x = sin( angle );
		rotateMat[1].y = cos( angle );

		// Reflect rotation in the object's matrix
		matrix *= rotateMat;

		// Update position
		rotation += angle;
	}

	void scale( const vec2& offset )
	{
		// Build a new matrix for calculation
		mat4 scaleMat;

		// Get the values to scale by
		scaleMat[0].x = offset.x;
		scaleMat[1].y = offset.y;

		// Reflect scale in the object's matrix
		matrix *= scaleMat;

		// Update scale
		scaleVector += offset;
	}

	void shear( const vec2& offset )
	{
		mat4 shearMat;

		shearMat[0].y = offset.x;
		shearMat[1].x = offset.y;

		matrix *= shearMat;
		shearVector += offset;
	}

	const mat4& getMatrix() const { return matrix; }

};

#endif