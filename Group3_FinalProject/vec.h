
#ifndef VEC_H
#define VEC_H

#include "includes.h"
#include <math.h>

class vec2
{

public:
	GLfloat x, y;

	// indexing (from Angel)
	 GLfloat& operator [] ( int i ) 
	 {
		 return *(&x + i); 
	 }
	 const GLfloat operator [] ( int i ) const 
	 {
		 return *(&x + i);
	  }

	// Constuctors

	vec2( void ) : x( 0.0 ), y( 0.0 ) {}
	vec2( GLfloat f ) : x( f ), y( f )  {}
	vec2( GLfloat x, GLfloat y ) : x( x ), y( y ) {}
	// copy constructor
	vec2( const vec2& otherVec2 ) : x( otherVec2.x ), y( otherVec2.y ) {}

	// copy assignment
	vec2& operator = ( const vec2& v )
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	
	//destructor
	~vec2( void )
	{
		// do nothing
	}

	// Vector arithmetic (from Angel)
	
    vec2 operator - () const // unary minus operator
	{
		return vec2( -x, -y );
	}

    vec2 operator + ( const vec2& v ) const
	{
		return vec2( x + v.x, y + v.y ); 
	}

    vec2 operator - ( const vec2& v ) const
	{ 
		return vec2( x - v.x, y - v.y ); 
	}

    vec2 operator * ( const GLfloat s ) const
	{
		return vec2( s*x, s*y ); 
	}

    vec2 operator * ( const vec2& v ) const
	{
		return vec2( x*v.x, y*v.y ); 
	}

    friend vec2 operator * ( const GLfloat s, const vec2& v )
	{ 
		return v * s; 
	}

    
	// modifiers

	vec2& operator += ( const vec2& v )
	{ 
		x += v.x; 
		y += v.y; 
		return *this;
	}

    vec2& operator -= ( const vec2& v )
	{ 
		x -= v.x; 
		y -= v.y; 
		return *this; 
	}

    vec2& operator *= ( const GLfloat s )
	{
		x *= s;
		y *= s; 
		return *this; 
	}

    vec2& operator *= ( const vec2& v )
	{ 
		x *= v.x;
		y *= v.y;
		return *this;
	}

    vec2& operator /= ( const GLfloat s ) 
	{
		GLfloat r = 1.0f / s;
		*this *= r;
		return *this;
    }

	// Dot product
	GLfloat operator * ( const vec2& v )
	{
		return ( x * v.x ) + ( y * v.y );
	}

	// cross product
	vec2* operator % ( const vec2& v )
	{
		return new vec2( x*v.y, - y*v.x );
	}

	// magnitude
	operator double ()
	{ 
		return static_cast<double>( sqrt( pow( x, 2 ) + pow( y, 2 ) ) ); 
	}

	// Triple cross-product
	friend vec2 tripleProduct( vec2 a, vec2 b, vec2 c )
	{
		GLfloat ca = c * a;
		GLfloat cb = c * b;
		return ( ca * b ) - ( cb * a );
	}

	friend vec2 normalize( vec2 a )
	{
		float len = sqrt( pow( a.x, 2 ) + pow( a.y, 2 ) );
		return vec2( a.x / len, a.y / len );
	}


}; // vec2


class vec3
{

public:
	GLfloat x, y, z;

	// Indexing (from Angel)

	 GLfloat& operator [] ( int i ) { return *(&x + i); }
    const GLfloat operator [] ( int i ) const { return *(&x + i); }


	// Constructors

	vec3( void ) : x( 0.0 ), y( 0.0 ), z( 0.0 ) {}
	vec3( GLfloat f ) : x( f ), y( f ), z( f )  {}
	vec3( GLfloat x, GLfloat y, GLfloat z ) : x( x ), y( y ), z( z ) {}
	// copy constructor
	vec3( const vec3& otherVec3 ) : x( otherVec3.x ), y( otherVec3.y ), z( otherVec3.z ) {}

	// copy assignment
	vec3& operator = ( const vec3& v )
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	} 

	//destructor
	~vec3( void )
	{
		// do nothing
	}

	// arithmetic (from Angel)

	vec3 operator - () const  // unary minus operator
	{ 
		return vec3( -x, -y, -z );
	}

    vec3 operator + ( const vec3& v ) const
	{
		return vec3( x + v.x, y + v.y, z + v.z );
	}

    vec3 operator - ( const vec3& v ) const
	{ 
		return vec3( x - v.x, y - v.y, z - v.z );
	}

    vec3 operator * ( const GLfloat s ) const
	{
		return vec3( s*x, s*y, s*z ); 
	}

    vec3 operator * ( const vec3& v ) const
	{
		return vec3( x*v.x, y*v.y, z*v.z );
	}

    friend vec3 operator * ( const GLfloat s, const vec3& v )
	{ 
		return v * s; 
	}

    vec3 operator / ( const GLfloat s ) const 
	{
		GLfloat r = GLfloat(1.0) / s;
		return *this * r;
    }

	// modifiers

    vec3& operator += ( const vec3& v )
	{ 
		x += v.x;  y += v.y;  z += v.z;  return *this; 
	}

    vec3& operator -= ( const vec3& v )
	{
		x -= v.x;  y -= v.y;  z -= v.z;  return *this; 
	}

    vec3& operator *= ( const GLfloat s )
	{ 
		x *= s;  y *= s;  z *= s;  return *this;
	}

    vec3& operator *= ( const vec3& v )
	{ 
		x *= v.x;  y *= v.y;  z *= v.z;  return *this; 
	}

    vec3& operator /= ( const GLfloat s ) 
	{
		GLfloat r = GLfloat(1.0) / s;
		*this *= r;
		return *this;
    }

	// Dot product
	GLfloat operator * ( const vec3& v )
	{
		return x*v.x + y*v.y + z*v.z;
	}

	// cross product
	vec3* operator % ( const vec3& v )
	{
		return new vec3( y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x );
	}

	// magnitude
	operator double()
	{
		return  static_cast<double>( sqrt( pow(x,2) + pow(y,2) + pow(z,2) ) );
	}


}; // vec3

class vec4 {

public:
    GLfloat  x;
    GLfloat  y;
    GLfloat  z;
    GLfloat  w;

    //
    //  --- Constructors and Destructors ---
    //

    vec4( GLfloat s = GLfloat(0.0) ) :
	x(s), y(s), z(s), w(s) {}

    vec4( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) :
	x(x), y(y), z(z), w(w) {}

    vec4( const vec4& v ) { x = v.x;  y = v.y;  z = v.z;  w = v.w; }

    vec4( const vec3& v, const float w = 1.0 ) : w(w)
	{ x = v.x;  y = v.y;  z = v.z; }

    vec4( const vec2& v, const float z, const float w ) : z(z), w(w)
	{ x = v.x;  y = v.y; }

    //
    //  --- Indexing Operator ---
    //

    GLfloat& operator [] ( int i ) { return *(&x + i); }
    const GLfloat operator [] ( int i ) const { return *(&x + i); }

    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    vec4 operator - () const  // unary minus operator
	{ return vec4( -x, -y, -z, -w ); }

    vec4 operator + ( const vec4& v ) const
	{ return vec4( x + v.x, y + v.y, z + v.z, w + v.w ); }

    vec4 operator - ( const vec4& v ) const
	{ return vec4( x - v.x, y - v.y, z - v.z, w - v.w ); }

    vec4 operator * ( const GLfloat s ) const
	{ return vec4( s*x, s*y, s*z, s*w ); }

    vec4 operator * ( const vec4& v ) const
	{ return vec4( x*v.x, y*v.y, z*v.z, w*v.z ); }

    friend vec4 operator * ( const GLfloat s, const vec4& v )
	{ return v * s; }

    vec4 operator / ( const GLfloat s ) const {
#ifdef DEBUG
	if ( std::fabs(s) < DivideByZeroTolerance ) {
	    std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
		      << "Division by zero" << std::endl;
	    return vec4();
	}
#endif // DEBUG

	GLfloat r = GLfloat(1.0) / s;
	return *this * r;
    }

    //
    //  --- (modifying) Arithematic Operators ---
    //

    vec4& operator += ( const vec4& v )
	{ x += v.x;  y += v.y;  z += v.z;  w += v.w;  return *this; }

    vec4& operator -= ( const vec4& v )
	{ x -= v.x;  y -= v.y;  z -= v.z;  w -= v.w;  return *this; }

    vec4& operator *= ( const GLfloat s )
	{ x *= s;  y *= s;  z *= s;  w *= s;  return *this; }

    vec4& operator *= ( const vec4& v )
	{ x *= v.x, y *= v.y, z *= v.z, w *= v.w;  return *this; }

    vec4& operator /= ( const GLfloat s ) {
#ifdef DEBUG
	if ( std::fabs(s) < DivideByZeroTolerance ) {
	    std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
		      << "Division by zero" << std::endl;
	}
#endif // DEBUG

	GLfloat r = GLfloat(1.0) / s;
	*this *= r;

	return *this;
    }
	
    //
    //  --- Insertion and Extraction Operators ---
    //

    friend std::ostream& operator << ( std::ostream& os, const vec4& v ) {
	return os << "( " << v.x << ", " << v.y
		  << ", " << v.z << ", " << v.w << " )";
    }

    friend std::istream& operator >> ( std::istream& is, vec4& v )
	{ return is >> v.x >> v.y >> v.z >> v.w; }

    //
    //  --- Conversion Operators ---
    //

    operator const GLfloat* () const
	{ return static_cast<const GLfloat*>( &x ); }

    operator GLfloat* ()
	{ return static_cast<GLfloat*>( &x ); }
};

//----------------------------------------------------------------------------
//
//  Non-class vec4 Methods
//

inline
GLfloat dot( const vec4& u, const vec4& v ) {
    return u.x*v.x + u.y*v.y + u.z*v.z + u.w+v.w;
}

inline
GLfloat length( const vec4& v ) {
    return std::sqrt( dot(v,v) );
}

inline
vec4 normalize( const vec4& v ) {
    return v / length(v);
}

inline
vec3 cross(const vec4& a, const vec4& b )
{
    return vec3( a.y * b.z - a.z * b.y,
		 a.z * b.x - a.x * b.z,
		 a.x * b.y - a.y * b.x );
}

#endif // VEC_H