// Implements GJK for collision detection
// Useful article: http://www.codezealot.org/archives/88

#include "Collision.h"
#include "AbstractGameObject.h"


Collision::Collision()
{
	collisionNormal = vec2( 0.0f, 0.0f );
	collisionDepth = 0;
}

Collision::~Collision()
{

}

// Implements GJK for collision detection
bool Collision::checkCollision( AbstractGameObject* obj1, AbstractGameObject* obj2 )
{
	//cout << "New collision Check" << endl;
	simplex.clear();

	vec2 searchDirection = obj1->rigidBody.getLinearVelocity();

	// Add a point on the edge of the shape
	simplex.push_back( simplexSupport( &obj1->mesh, &obj2->mesh, searchDirection ) );

	searchDirection = -searchDirection;

	while( true )
	{
		// Add a second point on the other side of the shape to create a line segment
		simplex.push_back( simplexSupport( &obj1->mesh, &obj2->mesh, searchDirection ) );

		// There is no way to reach the origin
		if( simplex.back() * searchDirection <= 0 )
			return false;
		else
		{
			// Check for collision by seeing if the simplex contains the origin
			if( simplexContainsOrigin( &simplex, &searchDirection ) )
			{
				EPA( &obj1->mesh, &obj2->mesh, &simplex );
				return true;
			}
		}
	}

	simplex.clear();
}

// Support function for simplex that finds 
vec2 Collision::simplexSupport( Mesh* mesh1, Mesh* mesh2, const vec2 direction )
{
	vec2 p1 = mesh1->getFarthestPoint( direction );
	//cout << p1.x << "   " << p1.y << endl;
	vec2 p2 = mesh2->getFarthestPoint( -direction );
	//cout << p2.x << "   " << p2.y << endl;
	return p1 - p2;
}

// Checks to see if the simplex is over the origin
bool Collision::simplexContainsOrigin( vector<vec2>* simplex, vec2* searchDir )
{
	vec2 a = simplex->back();

	vec2 ao = -a;

	// If the simplex is a triangle
	if( simplex->size() == 3 )
	{
		// vector b
		vec2 b = simplex->at( 0 );
		// vector c
		vec2 c = simplex->at( 1 );

		vec2 ab = b - a;
		vec2 ac = c - a;

		vec2 temp = ac * ab;

		// Error stem
		// ac X ab X ab
		vec2 abPerp = tripleProduct( ac, ab, ab );
		// ab X ac X ac
		vec2 acPerp = tripleProduct( ab, ac, ac );

		// Check region 1
		if( abPerp * ao > 0 )
		{
			// Remove c
			simplex->erase( simplex->begin() + 1 );
			*searchDir = abPerp;
		}
		else
		{
			// Check region 2
			if( acPerp * ao > 0 )
			{
				// Remove b
				simplex->erase( simplex->begin() + 0 );
				*searchDir = acPerp;
			}
			// Simplex contains origin
			else
				return true;
		}
	}
	// Simplex needs another point before checking for the origin
	else
	{
		vec2 b = simplex->front();
		vec2 ab = b - a;
		//ab X ao X ab
		vec2 abPerp = ( ab * ab * ao ) - ( ab * ao * ab );
		*searchDir = abPerp;
	}

	return false;
}

void Collision::findCollisionInformation( const vector<vec2>* simplex )
{

	float closestDistance = 500000000.0f;

	for( int i = 0; i < simplex->size(); i++ )
	{
		int j = i + 1 == simplex->size() ? 0 : i + 1;

		vec2 a = simplex->at( i );
		vec2 b = simplex->at( j );

		// edge
		vec2 edge = b - a;

		vec2 oa = a;

		// Not precise
		//vec2 normal = tripleProduct( edge, oa, edge );
		// Winding method
		vec2 normal = vec2( edge.y, -edge.x );

		normal = normalize( normal );

		float tempD = normal * b;

		if ( tempD < closestDistance )
		{
			collisionNormal = normal;
			collisionDepth = tempD;
			collisionIndex = j;
		}
	}

	return;
}

// Helpful description for EPA
// http://www.codezealot.org/archives/180
void Collision::EPA( Mesh* mesh1, Mesh* mesh2, vector<vec2>* simplex )
{
	while( true )
	{
		// Get the normal and depth of collision
		findCollisionInformation( simplex );
		
		// Build a new point for the simplex
		vec2 supportPoint = simplexSupport( mesh1, mesh2, collisionNormal );

		// Make a temp distance
		float tempD = supportPoint * collisionNormal;


		if( tempD - collisionDepth < TOLERANCE )
		{
			collisionDepth = tempD;
			return;
		}
		else
		{
			simplex->insert( simplex->begin() + collisionIndex, supportPoint );
		}
	}
}