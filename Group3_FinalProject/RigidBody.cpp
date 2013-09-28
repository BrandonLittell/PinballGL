#include "RigidBody.h"
#include "AbstractGameObject.h"



RigidBody::RigidBody( AbstractGameObject* own )
{
	owner = own;
	linearVelocity = vec2( 0.0f, 0.0f );
	angularVelocity = vec2( 0.0f, 0.0f );
	mass = 10;
}


RigidBody::~RigidBody( void )
{
}

void RigidBody::calculateGravity( float deltaTime )
{
	linearVelocity.y += GRAVITY * deltaTime;
}

void RigidBody::update( float deltaTime )
{
	calculateGravity( deltaTime );
	owner->transforms.translate( linearVelocity );
}


void RigidBody::reset()
{
	linearVelocity = vec2( 0.0f, 0.0f );
	angularVelocity = 0.0f;
}

void RigidBody::collisionResponse( float depth, vec2 normal, RigidBody* collidingBody )
{
	// Horizontal wall
	if( normal.x == 0 )
	{
		linearVelocity.y = -( linearVelocity.y * BOUNCE );
		//linearVelocity = calcLinearMomentum( collidingBody );
		//owner->transforms.translate( vec2( 0.0f, depth ) );
	}
	// Non-horizontal wall
	else 
	{
		// Vertical wall
		if( normal.y == 0 )
		{
			
			linearVelocity.x = -( linearVelocity.x * BOUNCE );
			//linearVelocity = calcLinearMomentum( collidingBody );
			//owner->transforms.translate( vec2( depth, 0.0f ) );
		}
		// Angled wall
		else
		{
			// Calculates the angle of the normal to collision surface
			//float normalAngle = atan2( normal.y, normal.x );
			float normalAngle = atan2( normal.y, normal.x );

			linearVelocity.x = BOUNCE * cos( normalAngle );
			linearVelocity.y = BOUNCE * sin( normalAngle );

			//linearVelocity = calcLinearMomentum( collidingBody );

			
		}
	}

	/*
	// Move the ball to prevent tunnelling
	float normalAngle = atan2( normal.y, normal.x );
	vec2 depthVec = vec2( depth * sin( normalAngle ), depth * cos( normalAngle ) );
	owner->transforms.translate( depthVec );
	*/

}

vec2 RigidBody::calcLinearMomentum( RigidBody* body2 )
{
	vec2 numerator = 2 * body2->getMass() * body2->getLinearVelocity() + ( mass - body2->mass ) * linearVelocity;
	vec2 body2Numerator = ( body2->mass - mass ) * body2->getLinearVelocity() + 2 * mass * linearVelocity;
	float denominator = body2->getMass() + mass;

	body2->setLinearVelocity( body2Numerator / denominator );

	return numerator / denominator;
}