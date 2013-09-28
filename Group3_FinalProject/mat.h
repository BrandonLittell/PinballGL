
#ifndef MAT_H
#define MAT_H

#include "vec.h"

//----------------------------------------------------------------------------
//
//  mat3 - 3D square matrix 
//

class mat3 {

private:
    vec3  _m[3];
public:
    //  --- Constructors and Destructors ---
    mat3( const GLfloat d = GLfloat(1.0) )  // Create a diagional matrix
	{ _m[0].x = d;  _m[1].y = d;  _m[2].z = d;   }

    mat3( const vec3& a, const vec3& b, const vec3& c )
	{ _m[0] = a;  _m[1] = b;  _m[2] = c;  }

    mat3( GLfloat m00, GLfloat m10, GLfloat m20,
	      GLfloat m01, GLfloat m11, GLfloat m21,
	      GLfloat m02, GLfloat m12, GLfloat m22 ) 
	{
	    _m[0] = vec3( m00, m01, m02 );
	    _m[1] = vec3( m10, m11, m12 );
	    _m[2] = vec3( m20, m21, m22 );
	}

    mat3( const mat3& m )
	{
	    if ( *this != m ) 
		{
			_m[0] = m._m[0];
			_m[1] = m._m[1];
			_m[2] = m._m[2];
	    } 
	}

    //  --- Indexing Operator ---
    vec3& operator [] ( int i ) { return _m[i]; }
    const vec3& operator [] ( int i ) const { return _m[i]; }


    //  --- (non-modifying) Arithmatic Operators ---
    mat3 operator + ( const mat3& m ) const
	{ return mat3( _m[0]+m[0], _m[1]+m[1], _m[2]+m[2] ); }

    mat3 operator - ( const mat3& m ) const
	{ return mat3( _m[0]-m[0], _m[1]-m[1], _m[2]-m[2] ); }

    mat3 operator * ( const GLfloat s ) const 
	{ return mat3( s*_m[0], s*_m[1], s*_m[2] ); }

    mat3 operator / ( const GLfloat s ) const 
	{
		GLfloat r = GLfloat(1.0) / s;
		return *this * r;
    }

    friend mat3 operator * ( const GLfloat s, const mat3& m )
	{ return m * s; }
	
    mat3 operator * ( const mat3& m ) const 
	{
		mat3  a( 0.0 );

		for ( int i = 0; i < 3; ++i ) {
			for ( int j = 0; j < 3; ++j )
			{
				for ( int k = 0; k < 3; ++k ) 
				{
					a[i][j] += _m[i][k] * m[k][j];
				}
			}
		}

		return a;
    }

    //  --- (modifying) Arithmetic Operators ---
    mat3& operator += ( const mat3& m ) 
	{
		_m[0] += m[0];  _m[1] += m[1];  _m[2] += m[2]; 
		return *this;
    }

    mat3& operator -= ( const mat3& m )
	{
		_m[0] -= m[0];  _m[1] -= m[1];  _m[2] -= m[2]; 
		return *this;
    }

    mat3& operator *= ( const GLfloat s ) 
	{
		_m[0] *= s;  _m[1] *= s;  _m[2] *= s; 
		return *this;
    }

    mat3& operator *= ( const mat3& m )
	{
		mat3  a( 0.0 );

		for ( int i = 0; i < 3; ++i ) {
			for ( int j = 0; j < 3; ++j ) 
			{
				for ( int k = 0; k < 3; ++k ) 
				{
					a[i][j] += _m[i][k] * m[k][j];
				}
			}
		}

		return *this = a;
    }

    mat3& operator /= ( const GLfloat s ) 
	{
		GLfloat r = GLfloat(1.0) / s;
		return *this *= r;
    }

    //  --- Matrix / Vector operators ---
    vec3 operator * ( const vec3& v ) const 
	{  // m * v
	return vec3( _m[0][0]*v.x + _m[0][1]*v.y + _m[0][2]*v.z,
		         _m[1][0]*v.x + _m[1][1]*v.y + _m[1][2]*v.z,
		         _m[2][0]*v.x + _m[2][1]*v.y + _m[2][2]*v.z );
    }
	
    //  --- Conversion Operators ---
    operator const GLfloat* () const
	{ return static_cast<const GLfloat*>( &_m[0].x ); }

    operator GLfloat* ()
	{ return static_cast<GLfloat*>( &_m[0].x ); }
};  // mat3

//  --- Non-class mat3 Methods ---
inline
mat3 matrixCompMult( const mat3& A, const mat3& B ) 
{
    return mat3( A[0][0]*B[0][0], A[0][1]*B[0][1], A[0][2]*B[0][2],
		         A[1][0]*B[1][0], A[1][1]*B[1][1], A[1][2]*B[1][2],
		         A[2][0]*B[2][0], A[2][1]*B[2][1], A[2][2]*B[2][2] );
}

inline
mat3 transpose( const mat3& A ) 
{
    return mat3( A[0][0], A[1][0], A[2][0],
		         A[0][1], A[1][1], A[2][1],
		         A[0][2], A[1][2], A[2][2] );
}



class mat4
{
private:
	vec4  _m[4];

public:
    //
    //  --- Constructors and Destructors ---
    //

    mat4( const GLfloat d = GLfloat(1.0) )  // Create a diagional matrix
	{ _m[0].x = d;  _m[1].y = d;  _m[2].z = d;  _m[3].w = d; }

    mat4( const vec4& a, const vec4& b, const vec4& c, const vec4& d )
	{ _m[0] = a;  _m[1] = b;  _m[2] = c;  _m[3] = d; }

    mat4( GLfloat m00, GLfloat m10, GLfloat m20, GLfloat m30,
	  GLfloat m01, GLfloat m11, GLfloat m21, GLfloat m31,
	  GLfloat m02, GLfloat m12, GLfloat m22, GLfloat m32,
	  GLfloat m03, GLfloat m13, GLfloat m23, GLfloat m33 )
	{
	    _m[0] = vec4( m00, m01, m02, m03 );
	    _m[1] = vec4( m10, m11, m12, m13 );
	    _m[2] = vec4( m20, m21, m22, m23 );
	    _m[3] = vec4( m30, m31, m32, m33 );
	}

    mat4( const mat4& m )
	{
	    if ( *this != m ) {
		_m[0] = m._m[0];
		_m[1] = m._m[1];
		_m[2] = m._m[2];
		_m[3] = m._m[3];
	    } 
	}

    //
    //  --- Indexing Operator ---
    //

    vec4& operator [] ( int i ) { return _m[i]; }
    const vec4& operator [] ( int i ) const { return _m[i]; }

    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    mat4 operator + ( const mat4& m ) const
	{ return mat4( _m[0]+m[0], _m[1]+m[1], _m[2]+m[2], _m[3]+m[3] ); }

    mat4 operator - ( const mat4& m ) const
	{ return mat4( _m[0]-m[0], _m[1]-m[1], _m[2]-m[2], _m[3]-m[3] ); }

    mat4 operator * ( const GLfloat s ) const 
	{ return mat4( s*_m[0], s*_m[1], s*_m[2], s*_m[3] ); }

    mat4 operator / ( const GLfloat s ) const {
#ifdef DEBUG
	if ( std::fabs(s) < DivideByZeroTolerance ) {
	    std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
		      << "Division by zero" << std::endl;
	    return mat4();
	}
#endif // DEBUG
	
	GLfloat r = GLfloat(1.0) / s;
	return *this * r;
    }

    friend mat4 operator * ( const GLfloat s, const mat4& m )
	{ return m * s; }
	
    mat4 operator * ( const mat4& m ) const {
	mat4  a( 0.0 );

	for ( int i = 0; i < 4; ++i ) {
	    for ( int j = 0; j < 4; ++j ) {
		for ( int k = 0; k < 4; ++k ) {
		    a[i][j] += _m[i][k] * m[k][j];
		}
	    }
	}

	return a;
    }

    //
    //  --- (modifying) Arithematic Operators ---
    //

    mat4& operator += ( const mat4& m ) {
	_m[0] += m[0];  _m[1] += m[1];  _m[2] += m[2];  _m[3] += m[3];
	return *this;
    }

    mat4& operator -= ( const mat4& m ) {
	_m[0] -= m[0];  _m[1] -= m[1];  _m[2] -= m[2];  _m[3] -= m[3];
	return *this;
    }

    mat4& operator *= ( const GLfloat s ) {
	_m[0] *= s;  _m[1] *= s;  _m[2] *= s;  _m[3] *= s;
	return *this;
    }

    mat4& operator *= ( const mat4& m ) {
	mat4  a( 0.0 );

	for ( int i = 0; i < 4; ++i ) {
	    for ( int j = 0; j < 4; ++j ) {
		for ( int k = 0; k < 4; ++k ) {
		    a[i][j] += _m[i][k] * m[k][j];
		}
	    }
	}

	return *this = a;
    }

    mat4& operator /= ( const GLfloat s ) {
#ifdef DEBUG
	if ( std::fabs(s) < DivideByZeroTolerance ) {
	    std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
		      << "Division by zero" << std::endl;
	    return mat4();
	}
#endif // DEBUG

	GLfloat r = GLfloat(1.0) / s;
	return *this *= r;
    }

    //
    //  --- Matrix / Vector operators ---
    //

    vec4 operator * ( const vec4& v ) const {  // m * v
	return vec4( _m[0][0]*v.x + _m[0][1]*v.y + _m[0][2]*v.z + _m[0][3]*v.w,
		     _m[1][0]*v.x + _m[1][1]*v.y + _m[1][2]*v.z + _m[1][3]*v.w,
		     _m[2][0]*v.x + _m[2][1]*v.y + _m[2][2]*v.z + _m[2][3]*v.w,
		     _m[3][0]*v.x + _m[3][1]*v.y + _m[3][2]*v.z + _m[3][3]*v.w
	    );
    }
	
    //
    //  --- Insertion and Extraction Operators ---
    //
	
    friend std::ostream& operator << ( std::ostream& os, const mat4& m ) {
	return os << std::endl 
		  << m[0] << std::endl
		  << m[1] << std::endl
		  << m[2] << std::endl
		  << m[3] << std::endl;
    }

    friend std::istream& operator >> ( std::istream& is, mat4& m )
	{ return is >> m._m[0] >> m._m[1] >> m._m[2] >> m._m[3]; }

    //
    //  --- Conversion Operators ---
    //

    operator const GLfloat* () const
	{ return static_cast<const GLfloat*>( &_m[0].x ); }

    operator GLfloat* ()
	{ return static_cast<GLfloat*>( &_m[0].x ); }
}; // mat4

//
//  --- Non-class mat4 Methods ---
//

inline
mat4 matrixCompMult( const mat4& A, const mat4& B ) {
    return mat4(
	A[0][0]*B[0][0], A[0][1]*B[0][1], A[0][2]*B[0][2], A[0][3]*B[0][3],
	A[1][0]*B[1][0], A[1][1]*B[1][1], A[1][2]*B[1][2], A[1][3]*B[1][3],
	A[2][0]*B[2][0], A[2][1]*B[2][1], A[2][2]*B[2][2], A[2][3]*B[2][3],
	A[3][0]*B[3][0], A[3][1]*B[3][1], A[3][2]*B[3][2], A[3][3]*B[3][3] );
}

inline
mat4 transpose( const mat4& A ) {
    return mat4( A[0][0], A[1][0], A[2][0], A[3][0],
		 A[0][1], A[1][1], A[2][1], A[3][1],
		 A[0][2], A[1][2], A[2][2], A[3][2],
		 A[0][3], A[1][3], A[2][3], A[3][3] );
}

inline
mat4 Translate( const GLfloat x, const GLfloat y, const GLfloat z )
{
    mat4 c;
    c[0][3] = x;
    c[1][3] = y;
    c[2][3] = z;
    return c;
}

//----------------------------------------------------------------------------
//
//  Scale matrix generators
//

inline
mat4 Scale( const GLfloat x, const GLfloat y, const GLfloat z )
{
    mat4 c;
    c[0][0] = x;
    c[1][1] = y;
    c[2][2] = z;
    return c;
}

inline
mat4 Scale( const vec3& v )
{
    return Scale( v.x, v.y, v.z );
}

//
//  Helpful Matrix Methods
//
inline
mat4 Ortho( const GLfloat left, const GLfloat right,
	    const GLfloat bottom, const GLfloat top,
	    const GLfloat zNear, const GLfloat zFar )
{
    mat4 c;
    c[0][0] = static_cast<GLfloat>(2.0/(right - left));
    c[1][1] = static_cast<GLfloat>(2.0/(top - bottom));
    c[2][2] = static_cast<GLfloat>(2.0/(zNear - zFar));
    c[3][3] = static_cast<GLfloat>(1.0);
    c[0][3] = static_cast<GLfloat>(-(right + left)/(right - left));
    c[1][3] = static_cast<GLfloat>(-(top + bottom)/(top - bottom));
    c[2][3] = static_cast<GLfloat>(-(zFar + zNear)/(zFar - zNear));
    return c;
}

inline
mat4 Ortho2D( const GLfloat left, const GLfloat right,
	      const GLfloat bottom, const GLfloat top )
{
    return Ortho( left, right, bottom, top, -1.0, 1.0 );
}

#endif