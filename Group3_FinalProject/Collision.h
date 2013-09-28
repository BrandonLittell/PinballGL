
#ifndef COLLISION_H
#define COLLISION_H

#include "includes.h"
#include "AbstractGameObject.h"
#include <vector>

static const float TOLERANCE = 0.00001f;

struct Collision
{
private:
	vec2 collisionNormal;
	float collisionDepth;
	int collisionIndex;
	vector<vec2> simplex;
	vec2 simplexSupport( Mesh* mesh1, Mesh* mesh2, const vec2 direction );
	bool simplexContainsOrigin( vector<vec2>* simplex, vec2* searchDir );
	void findCollisionInformation( const vector<vec2>* simplex );
	void EPA( Mesh* mesh1, Mesh* mesh2, vector<vec2>* simplex );
public:
	Collision( void );
	~Collision( void );
	bool checkCollision( AbstractGameObject* obj1, AbstractGameObject* obj2 );
	float getCollisionDepth() { return collisionDepth; }
	vec2 getCollisionNormal() { return -collisionNormal; }
};

#endif