
#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "includes.h"
#include "mat.h"

#define GRAVITY -1.7f
static const float FRICTION = 0.95f;
static const float BOUNCE = 0.60f;

// Forward Declaration to remove circular dependency
class AbstractGameObject;

struct RigidBody
{
private:
	// Pointer to owning object; used for transformations
	AbstractGameObject* owner;
	vec2 linearVelocity;
	void calculateGravity( float deltaTime );
	vec2 calcLinearMomentum( RigidBody* body2 );
public:
	float angularVelocity;
	GLfloat mass;
	RigidBody( AbstractGameObject* own );
	~RigidBody( void );
	void update( float deltaTime );
	void reset();
	const vec2 getLinearVelocity() { return linearVelocity; }
	const vec2 getMass() { return mass; }
	void stop() { linearVelocity = vec2( 0.0f, 0.0f ); }
	void setLinearVelocity( vec2 linVel ) { linearVelocity = linVel; }
	void addLinearVelocity( vec2 linVel ) { linearVelocity += linVel; }
	void collisionResponse( float depth, vec2 normal, RigidBody* collidingBody );
};

#endif

