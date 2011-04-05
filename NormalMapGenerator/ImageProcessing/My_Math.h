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

#ifndef __MY_MATH_H__
#define __MY_MATH_H__

#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include "HLSL_Func.h"

using namespace std;

#define MAX(a, b)  (a >= b? a : b)
#define MAX3(a,b,c) (MAX(a, MAX(b, c)))
#define MIN(a, b)  (a <= b? a : b)
#define MIN3(a,b,c) (MIN(a, MIN(b, c)))
#define ABS(a)     (a >= 0? a : -a)
//#define PI         3.141592653589793
#define RAD        0.017453292519943 // PI/180

enum Colors{ RED, GREEN, BLUE };

struct pix_f
{
	float r;
	float g;
	float b;
};

struct ray
{
        float x;
        float y;
        float z;
};

double rsqrt(double x);
float dot(ray a, ray b);
float3 GetNormal( float down, float up, float right, float left );
ray normalize( ray n );
float torad(float deg);
float3 ret_deriv( float3 n );
void limit_num(int & num, int limit);
unsigned char ComputeSobel(unsigned char ul, unsigned char um, unsigned char ur, unsigned char ml,
                           unsigned char mm, unsigned char mr, unsigned char ll, unsigned char lm,
						   unsigned char lr, float fScale );
float ComputeSobel(float ul, float um, float ur, float ml, float mm, float mr, float ll,
				   float lm, float lr, float fScale );

#endif
