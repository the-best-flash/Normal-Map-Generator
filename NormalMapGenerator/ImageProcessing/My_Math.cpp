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

#include "My_Math.h"

void limit_num(int & num, int limit)
{
        if( num > limit )
        {
                while( num > limit )
                        num -= limit;
        } else if ( num < 0 )
        {
                while( num < 0 )
                        num += limit;
        }
}

float torad(float deg)
{
	return (float)(deg * RAD);
}

double rsqrt(double x)
{
	return 1/sqrt(x);
}

float dot(ray a, ray b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float3 GetNormal( float down, float up, float right, float left )
{
	float3 n;

	n.x = (float)(left - right);
	n.y = (float)(down - up);
	//n.z = 2.0f;
	n.z = 1.0f;
	return normalize(n);
}

float3 ret_deriv( float3 n )
{
	n.x /= n.z;
	n.y /= n.z;
	n.z = 1;

	return n;
}

//Modified from code 
//Copyright 1993-2006 NVIDIA Corporation
unsigned char ComputeSobel(unsigned char ul, // upper left
						   unsigned char um, // upper middle
						   unsigned char ur, // upper right
						   unsigned char ml, // middle left
						   unsigned char mm, // middle (unused)
						   unsigned char mr, // middle right
						   unsigned char ll, // lower left
						   unsigned char lm, // lower middle
						   unsigned char lr, // lower right
						   float fScale )
{
    int Horz = ur + 2*mr + lr - ul - 2*ml - ll;
    int Vert = ul + 2*um + ur - ll - 2*lm - lr;
    int Sum = (int)(fScale*(ABS(Horz)+ABS(Vert)));

    if ( Sum < 0 ) 
		return 0; 
	else if ( Sum > 0xff ) 
		return 0xff;

    return (unsigned char) Sum;
}

//Modified from code 
//Copyright 1993-2006 NVIDIA Corporation
float ComputeSobel(float ul, // upper left
				   float um, // upper middle
				   float ur, // upper right
				   float ml, // middle left
				   float mm, // middle (unused)
				   float mr, // middle right
				   float ll, // lower left
				   float lm, // lower middle
				   float lr, // lower right
				   float fScale )
{
    float Horz = ur + 2*mr + lr - ul - 2*ml - ll;
    float Vert = ul + 2*um + ur - ll - 2*lm - lr;
    float Sum = fScale*(ABS(Horz)+ABS(Vert));

    if ( Sum < 0.0f ) 
		return 0; 
	else if ( Sum > 1.0f ) 
		return 1.0f;

    return Sum;
}
