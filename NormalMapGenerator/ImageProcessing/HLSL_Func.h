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

/** \file HLSL_Func.h
* Contains functions that have been converted from HLSL to C++
*/

#ifndef __HLSL_FUNC__H__
#define __HLSL_FUNC__H__

#include <cmath>
#include <omp.h>
using namespace std;

struct float2
{
	float x;
	float y;
};

struct float3
{
	float x;
	float y;
	float z;
};

struct float4
{
	float x;
	float y;
	float z;
	float w;
};

float* cross( float a[], float b[] );
float3 cross( float3 a, float3 b );
float rsqrt( float num );
float max_num(float x, float y);
float saturate(float num);
void normalize(float vector[]);
float3 normalize(float3 &vector);
float length(float x1, float x2, float y1, float y2, float z1, float z2);
float length(float x, float y, float z);
float length(float vector[]);
float length(float3 vector);
float length(float begin[], float end[]);
float dot( float vector1[], float vector2[] );
float dot( float3 vector1, float3 vector2 );

float3 operator ++(float3 a);
float3 operator --(float3 a);
float3 operator +(float3 a, float3 b);
float3 operator -(float3 a, float3 b);
float3 operator *(float3 a, float3 b);
float3 operator /(float3 a, float3 b);
float3 operator +(float3 a, float b);
float3 operator +(float a, float3 b);
float3 operator -(float3 a, float b);
float3 operator *(float3 a, float b);
float3 operator *(float a, float3 b);
float3 operator /(float3 a, float b);

float3 operator +=(float3 &a, float3 b);
float3 operator -=(float3 &a, float3 b);
float3 operator *=(float3 &a, float3 b);
float3 operator /=(float3 &a, float3 b);
float3 operator +=(float3 &a, float b);
float3 operator -=(float3 &a, float b);
float3 operator *=(float3 &a, float b);
float3 operator /=(float3 &a, float b);

float4 operator ++(float4 a);
float4 operator --(float4 a);
float4 operator +(float4 a, float4 b);
float4 operator -(float4 a, float4 b);
float4 operator *(float4 a, float4 b);
float4 operator /(float4 a, float4 b);
float4 operator +(float4 a, float b);
float4 operator +(float a, float4 b);
float4 operator -(float4 a, float b);
float4 operator *(float4 a, float b);
float4 operator *(float a, float4 b);
float4 operator /(float4 a, float b);

float4 operator +=(float4 &a, float4 b);
float4 operator -=(float4 &a, float4 b);
float4 operator *=(float4 &a, float4 b);
float4 operator /=(float4 &a, float4 b);
float4 operator +=(float4 &a, float b);
float4 operator -=(float4 &a, float b);
float4 operator *=(float4 &a, float b);
float4 operator /=(float4 &a, float b);

float4 make_float4(float x, float y, float z, float w);

#endif
