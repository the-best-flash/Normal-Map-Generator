/***************************************************************************
    Normal Map Generator Copyright © 2010 Colton Manville
    (Contact: the_best_flash@hotmail.com)

    This file is part of Normal Map Generator.

    Normal Map Generator is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Normal Map Generator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Normal Map Generator.

    If not, see <http://www.gnu.org/licenses/gpl.txt>.
***************************************************************************/

/** \file HLSL_Func.cpp
* Contains functions that have been converted from HLSL to C++
*/
#include "HLSL_Func.h"

/*! Calculates the cross product of two vectors. (Vector = float array w/ 3 elements)
	 \note Used to find the vector perpendicular to the plane formed by two vectors
	 \param[in] a[] float array with 3 elements. Represents a vector.
	 \param[in] b[] float array with 3 elements. Represents a vector. */
float * cross( float a[], float b[] ) 
{
	float * c = new float[3];
	//float c[3] = { 0 };

	c[0] = ((a[1] * b[2]) - (a[2] * b[1])) ;//* -1.0;
	c[1] = ((a[2] * b[0]) - (a[0] * b[2])) ;//* -1.0;
	c[2] = ((a[0] * b[1]) - (a[1] * b[0])) ;//* -1.0;

	return c;
}


float3 cross( float3 a, float3 b )
{
	float3 c;

	c.x = ((a.y * b.z) - (a.z * b.y)) ;
	c.y = ((a.z * b.x) - (a.x * b.z)) ;
	c.z = ((a.x * b.y) - (a.y * b.x)) ;

	return c;
}


/*! Calculates 1 devided by the square root of num.
	 \param[in] num The number to use in the calculation */
float rsqrt( float num )
{
	return (1/sqrt(num));
}

/*! Returns the larger of two values.
	 \param[in] x Value 1
	 \param[in] y Value 2 */
float max_num(float x, float y)
{
	return (x >= y? x : y);
}

/*! Calculates the length of a line drawn between two 3-D coordinates (X1,Y1,Z1) and (X2,Y2,Z2).
	 \param[in] x1 X coordinate 1
	 \param[in] x2 X coordinate 2
	 \param[in] y1 Y coordinate 1
	 \param[in] y2 Y coordinate 2
	 \param[in] z1 Z coordinate 1
	 \param[in] z2 Z coordinate 2 */
float length(float x1, float x2, float y1, float y2, float z1, float z2)
{
	float a, b, c;

	a = x1 - x2;
	b = y1 - y2;
	c = z1 - z2;

	return abs(sqrt( a*a + b*b + c*c ));
}	

/*! Calculates the length of a line drawn between the coordinates (0,0,0) and (X,Y,Z)
	 \param[in] x The X coordinate
	 \param[in] y The Y coordinate
	 \param[in] z The Z coordinate */
float length(float x, float y, float z)
{
	return abs(sqrt( x*x + y*y + z*z ));
}

/*! Calculates the length of a vector
	 \param[in] vector[] A float array with 3 elements. */
float length(float vector[])
{
	return sqrt( vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2] );
}


float length(float3 vector)
{
	return sqrt( vector.x * vector.x + vector.y * vector.y + vector.z * vector.z );
}


/*! Calculates the length of a line between (X,Y,Z) and (X2,Y2,Z2)
	 \param[in] begin[] A float array with 3 elements that represtents the begining coordinates of the line
	 \param[in] end[] A float array with 3 elements that represtents the ending coordinates of the line */
float length(float begin[], float end[])
{
	float a, b, c;

	a = end[0] - begin[0];
	b = end[1] - begin[1];
	c = end[2] - begin[2];

	return abs(sqrt( a*a + b*b + c*c ));
}

/*! Normalizes a vector. (Makes it a length of 1)
	 \param[in] vector[] A float array with 3 elements representing an array */
void normalize(float vector[])
{
	float len = length(vector[0], vector[1], vector[2]);

	vector[0] /= len;
	vector[1] /= len;
	vector[2] /= len;
}


float3 normalize(float3 &vector)
{
	float len = length( vector );

        vector /= len;

	return vector;
}


/*! Limits a number so that it is between 0.0 and 1.0
	 \param[in] num Number to be limited */
float saturate(float num)
{
	if(num > 1.0)
		return 1.0;
	else if(num < 0.0)
		return 0.0;

	return num;
}

/*! Returns the dot product of two vectors
	 \param[in] vector1[] A float array with 3 elements representing a vector.
	 \param[in] vector2[] A float array with 3 elements representing a vector. */
float dot( float vector1[], float vector2[] )
{
	return (vector1[0] * vector2[0]) + (vector1[1] * vector2[1]) + (vector1[2] * vector2[2]);
}

float dot( float3 vector1, float3 vector2 )
{
	return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

float3 operator ++(float3 a)
{
	float3 c;

	c.x = a.x + 1.0f;
	c.y = a.y + 1.0f;
	c.z = a.z + 1.0f;

	return c;
}

float3 operator --(float3 a)
{
	float3 c;

	c.x = a.x - 1.0f;
	c.y = a.y - 1.0f;
	c.z = a.z - 1.0f;

	return c;
}

float3 operator +(float3 a, float3 b)
{
    float3 tmp;

    tmp.x = a.x + b.x;
    tmp.y = a.y + b.y;
    tmp.z = a.z + b.z;

    return tmp;
}

float3 operator -(float3 a, float3 b)
{
     float3 tmp;

     tmp.x = a.x - b.x;
     tmp.y = a.y - b.y;
     tmp.z = a.z - b.z;

     return tmp;
}

float3 operator *(float3 a, float3 b)
{
    float3 tmp;

    tmp.x = a.x * b.x;
    tmp.y = a.y * b.y;
    tmp.z = a.z * b.z;

    return tmp;
}

float3 operator /(float3 a, float3 b)
{
    float3 tmp;

    tmp.x = a.x / b.x;
    tmp.y = a.y / b.y;
    tmp.z = a.z / b.z;

    return tmp;
}

float3 operator +(float3 a, float b)
{
    float3 tmp;

    tmp.x = a.x + b;
    tmp.y = a.y + b;
    tmp.z = a.z + b;

    return tmp;
}

float3 operator +(float a, float3 b)
{
    float3 tmp;

    tmp.x = b.x + a;
    tmp.y = b.y + a;
    tmp.z = b.z + a;

    return tmp;
}

float3 operator -(float3 a, float b)
{
    float3 tmp;

    tmp.x = a.x - b;
    tmp.y = a.y - b;
    tmp.z = a.z - b;

    return tmp;
}

float3 operator *(float3 a, float b)
{
    float3 tmp;

    tmp.x = a.x * b;
    tmp.y = a.y * b;
    tmp.z = a.z * b;

    return tmp;
}

float3 operator *(float a, float3 b)
{
    float3 tmp;

    tmp.x = b.x * a;
    tmp.y = b.y * a;
    tmp.z = b.z * a;

    return tmp;
}

float3 operator /(float3 a, float b)
{
    float3 tmp;

    tmp.x = a.x / b;
    tmp.y = a.y / b;
    tmp.z = a.z / b;

    return tmp;
}

float3 operator +=(float3 &a, float3 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    float3 tmp = a;
    return tmp;
}

float3 operator -=(float3 &a, float3 b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    float3 tmp = a;
    return tmp;
}

float3 operator *=(float3 &a, float3 b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;

    float3 tmp = a;
    return tmp;
}

float3 operator /=(float3 &a, float3 &b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;

    float3 tmp = a;
    return tmp;
}

float3 operator +=(float3 &a, float b)
{
    a.x += b;
    a.y += b;
    a.z += b;

    float3 tmp = a;
    return tmp;
}

float3 operator -=(float3 &a, float b)
{
    a.x -= b;
    a.y -= b;
    a.z -= b;

    float3 tmp = a;
    return tmp;
}

float3 operator *=(float3 &a, float b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;

    float3 tmp = a;
    return tmp;
}

float3 operator /=(float3 &a, float b)
{
    a.x /= b;
    a.y /= b;
    a.z /= b;

    float3 tmp = a;
    return tmp;
}

float4 operator ++(float4 a)
{
        float4 c;

        c.x = a.x + 1.0f;
        c.y = a.y + 1.0f;
        c.z = a.z + 1.0f;
        c.w = a.w + 1.0f;

        return c;
}

float4 operator --(float4 a)
{
        float4 c;

        c.x = a.x - 1.0f;
        c.y = a.y - 1.0f;
        c.z = a.z - 1.0f;
        c.w = a.w - 1.0f;

        return c;
}

float4 operator +(float4 a, float4 b)
{
    float4 tmp;

    tmp.x = a.x + b.x;
    tmp.y = a.y + b.y;
    tmp.z = a.z + b.z;
    tmp.w = a.w + b.w;

    return tmp;
}

float4 operator -(float4 a, float4 b)
{
     float4 tmp;

     tmp.x = a.x - b.x;
     tmp.y = a.y - b.y;
     tmp.z = a.z - b.z;
     tmp.w = a.w - b.w;

     return tmp;
}

float4 operator *(float4 a, float4 b)
{
    float4 tmp;

    tmp.x = a.x * b.x;
    tmp.y = a.y * b.y;
    tmp.z = a.z * b.z;
    tmp.w = a.w * b.w;

    return tmp;
}

float4 operator /(float4 a, float4 b)
{
    float4 tmp;

    tmp.x = a.x / b.x;
    tmp.y = a.y / b.y;
    tmp.z = a.z / b.z;
    tmp.w = a.w / b.w;

    return tmp;
}

float4 operator +(float4 a, float b)
{
    float4 tmp;

    tmp.x = a.x + b;
    tmp.y = a.y + b;
    tmp.z = a.z + b;
    tmp.w = a.w + b;

    return tmp;
}

float4 operator +(float a, float4 b)
{
    float4 tmp;

    tmp.x = b.x + a;
    tmp.y = b.y + a;
    tmp.z = b.z + a;
    tmp.w = b.w + a;

    return tmp;
}

float4 operator -(float4 a, float b)
{
    float4 tmp;

    tmp.x = a.x - b;
    tmp.y = a.y - b;
    tmp.z = a.z - b;
    tmp.w = a.w - b;

    return tmp;
}

float4 operator *(float4 a, float b)
{
    float4 tmp;

    tmp.x = a.x * b;
    tmp.y = a.y * b;
    tmp.z = a.z * b;
    tmp.w = a.w * b;

    return tmp;
}

float4 operator *(float a, float4 b)
{
    float4 tmp;

    tmp.x = b.x * a;
    tmp.y = b.y * a;
    tmp.z = b.z * a;
    tmp.w = b.w * a;

    return tmp;
}

float4 operator /(float4 a, float b)
{
    float4 tmp;

    tmp.x = a.x / b;
    tmp.y = a.y / b;
    tmp.z = a.z / b;
    tmp.w = a.w / b;

    return tmp;
}

float4 operator +=(float4 &a, float4 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;

    float4 tmp = a;
    return tmp;
}

float4 operator -=(float4 &a, float4 b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;

    float4 tmp = a;
    return tmp;
}

float4 operator *=(float4 &a, float4 b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;

    float4 tmp = a;
    return tmp;
}

float4 operator /=(float4 &a, float4 b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= a.w;

    float4 tmp = a;
    return tmp;
}

float4 operator +=(float4 &a, float b)
{
    a.x += b;
    a.y += b;
    a.z += b;
    a.w += b;

    float4 tmp = a;
    return tmp;
}

float4 operator -=(float4 &a, float b)
{
    a.x -= b;
    a.y -= b;
    a.z -= b;
    a.w -= b;

    float4 tmp = a;
    return tmp;
}

float4 operator *=(float4 &a, float b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    a.w *= b;

    float4 tmp = a;
    return tmp;
}

float4 operator /=(float4 &a, float b)
{
    a.x /= b;
    a.y /= b;
    a.z /= b;
    a.w /= b;

    float4 tmp = a;
    return tmp;
}

float4 make_float4(float x, float y, float z, float w)
{
    float4 tmp;

    tmp.x = x;
    tmp.y = y;
    tmp.z = z;
    tmp.w = w;

    return tmp;
}
