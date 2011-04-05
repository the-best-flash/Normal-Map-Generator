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

#include <omp.h>
#include "TextureMaster.h"
#include "My_Math.h"

//Equations from http://en.wikipedia.org/wiki/Gaussian_blur
void GenerateExp(float range, float* expMatrix)
{
	int r = (int)ceil(range);
	float sigma_sq = range / 3.0f;
	sigma_sq *= sigma_sq * 2;

	int i;

	#pragma omp parallel for
	for( i = 0; i <= r; i++ )
        expMatrix[i] = exp(-i*i/sigma_sq);
}

//Equations from http://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/MANDUCHI1/Bilateral_Filtering.html
void BilateralFilter(float3 *src, float3 *dest, int height, int width, float radius, float* cExp, float* sExp )
{
	int i;
	int size = height * width;
	int r = (int)ceil(radius);
	
	#pragma omp parallel
	{
		char padding[64];
		padding[0] = 0;

		#pragma omp for
                for( i = 0; i < size; i++ )
		{
			int x, y;
			float val;
			int row, col;
			int row2, col2;
			float sum;
			float result;
			float temp;

			row = i / width;
			col = i % width;
			sum = 0;
			result = 0;

			for( x = -r; x <= r; x++ )
			{
				for( y = -r; y <= r; y++ )
				{
					row2 = row + y;
					col2 = col + x;

					if( row2 >= height )
						row2 %= height;
					else
						while( row2 < 0 )
							row2 += height;

					if( col2 >= width )
						col2 %= width;
					else
						while( col2 < 0 )
							col2 += width;

					val = src[row2 * width + col2].x * 255;

					if( val > 255.0f )
						val = 255.0f;

					temp = cExp[abs(x)] * cExp[abs(y)] * sExp[(int)val];
					sum += temp;
					result += src[row2 * width + col2].x * 255 * temp;
				}
			}

			result /= sum;
			dest[i].x = dest[i].y = dest[i].z = result / 255.0f;
		}
	}
}

//Equations from http://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/MANDUCHI1/Bilateral_Filtering.html
void BilateralFilter(float *src, float *dest, int height, int width, float radius, float* cExp, float* sExp )
{
	int i;
	int size = height * width;
	int r = (int)ceil(radius);

	#pragma omp parallel
	{
		char padding[64]; //Prevent false sharing with padding
		padding[0] = 0; //Prevent compiler from optimizing away the padding

		#pragma omp for
		for( i = 0; i < size; i++ )
		{
			float sum;
			float result;
			float temp;
			int row, col;
			int row2, col2;
			float val;
			int x, y;

			row = i / width;
			col = i % width;
			sum = 0;
			result = 0;

			for( x = -r; x <= r; x++ )
			{
				for( y = -r; y <= r; y++ )
				{
					row2 = row + y;
					col2 = col + x;

					if( row2 >= height )
						row2 %= height;
					else
						while( row2 < 0 )
							row2 += height;

					if( col2 >= width )
						col2 %= width;
					else
						while( col2 < 0 )
							col2 += width;

					val = abs(src[row2 * width + col2] - src[i]) * 255;

					if( val > 255 )
					{
						val = 255;
					}

					temp = cExp[abs(x)] * cExp[abs(y)] * sExp[(int)val];
					sum += temp;
					result += src[row2 * width + col2] * 255 * temp;
				}
			}

			result /= sum;
			dest[i] = result / 255.0f;
		}
	}
}

void Grayscale(float3 *src, float3 *dest, int height, int width)
{
	int i;
	int size = height * width;

	#pragma omp parallel for
	for( i = 0; i < size; i ++ )
		dest[i].x = dest[i].y = dest[i].z = (.299f*src[i].x + .587f*src[i].y + .114f*src[i].z);
}

void Grayscale(float3 *src, float *dest, int height, int width)
{
	int i;
	int size = height * width;

	#pragma omp parallel for
	for( i = 0; i < size; i ++)
		dest[i] = (.299f * src[i].x + .587f * src[i].y + .114f * src[i].z);
}

void Normal2SSBump(unsigned char *data, int height, int width, Modes mode)
{
	//float3 green_vector = make_float3((float)(-rsqrt(6.0f)), (float)(rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 blue_vector = make_float3((float)(-rsqrt(6.0f)), (float)(-rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 red_vector = make_float3((float)(sqrt(2.0f)/sqrt(3.0f)), 0.0f, (float)(rsqrt(3.0f)));

	float3 green_vector = make_float3( -0.40824829f,  0.70710678f, 0.57735027f );
	float3 blue_vector  = make_float3( -0.40824829f, -0.70710678f, 0.57735027f );
	float3 red_vector   = make_float3(  0.92210791f,  0.00000000f, 0.57735027f );

	int i;

	switch( mode )
	{
	case N_DOT_L:
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )
		{
			float3 normal;
			int pos;
			float sum;
			float r, g, b;

			pos = i * 3;

			normal.x = data[pos] / 127.5f - 1.0f;
			normal.y = data[pos + 1] / 127.5f - 1.0f;
			normal.z = data[pos + 2] / 127.5f - 1.0f;

			r = saturate(dot( normal, red_vector ));
			g = saturate(dot( normal, green_vector ));
			b = saturate(dot( normal, blue_vector ));

			sum = r + g + b;
			data[pos] = (unsigned char)((r / sum) * 255);
			data[pos + 1] = (unsigned char)((g / sum) * 255);
			data[pos + 2] = (unsigned char)((b / sum) * 255);
		}
		break;
	case N_DOT_L2:
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )
		{
			float3 normal;
			int pos;
			float temp;
			float sum;
			float r, g, b;

			pos = i * 3;
			sum = 0;

			normal.x = data[pos] / 127.5f - 1.0f;
			normal.y = data[pos + 1] / 127.5f - 1.0f;
			normal.z = data[pos + 2] / 127.5f - 1.0f;

			temp = saturate(dot( normal, red_vector ));
			r = temp * temp;
			sum += r;

			temp = saturate(dot( normal, green_vector ));
			g = temp * temp;
			sum += g;

			temp = saturate(dot( normal, blue_vector ));
			b = temp * temp;
			sum += b;

			data[pos] = (unsigned char)((r / sum) * 255);
			data[pos + 1] = (unsigned char)((g / sum) * 255);
			data[pos + 2] = (unsigned char)((b / sum) * 255);
		}
		break;
/*	case N_DOT_L2:
		for( i = thread_id; i < height * width; i += processors )
		{
			pos = i * 3;

			normal.x = data[pos] / 127.5f - 1.0f;
			normal.y = data[pos + 1] / 127.5f - 1.0f;
			normal.z = data[pos + 2] / 127.5f - 1.0f;

			temp = saturate(dot( normal, red_vector ));
			data[pos] = (unsigned char)(temp * temp * 255);

			temp = saturate(dot( normal, green_vector ));
			data[pos + 1] = (unsigned char)( temp * temp * 255);

			temp = saturate(dot( normal, blue_vector ));
			data[pos + 2] = (unsigned char)( temp * temp * 255);
		}
		break; */
	case N_DOT_L4:
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )
		{
			float3 normal;
			int pos;
			float temp;
                        float r, g, b;
                        float sum;

			pos = i * 3;

			normal.x = data[pos] / 127.5f - 1.0f;
			normal.y = data[pos + 1] / 127.5f - 1.0f;
			normal.z = data[pos + 2] / 127.5f - 1.0f;
			
			temp =  1 - saturate(dot( normal, red_vector ));
			temp = temp * temp;
			temp *= temp;
                        r = 1 - temp;

			temp =  1 - saturate(dot( normal, green_vector ));
			temp = temp * temp;
			temp *= temp;
                        g = 1 - temp;

			temp =  1 - saturate(dot( normal, blue_vector ));
			temp = temp * temp;
			temp *= temp;
                        b = 1 - temp;

                        sum = r + g + b;
                        data[pos] = (unsigned char)((r / sum) * 255);
                        data[pos + 1] = (unsigned char)((g / sum) * 255);
                        data[pos + 2] = (unsigned char)((b / sum) * 255);
		}
		break;
	}
}

void Normal2SSBump(float3 *data, int height, int width, Modes mode)
{
	//float3 green_vector = make_float3((float)(-rsqrt(6.0f)), (float)(rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 blue_vector = make_float3((float)(-rsqrt(6.0f)), (float)(-rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 red_vector = make_float3((float)(sqrt(2.0f)/sqrt(3.0f)), 0.0f, (float)(rsqrt(3.0f)));

	float3 green_vector = make_float3( -0.40824829f,  0.70710678f, 0.57735027f );
	float3 blue_vector  = make_float3( -0.40824829f, -0.70710678f, 0.57735027f );
	float3 red_vector   = make_float3(  0.92210791f,  0.00000000f, 0.57735027f );

	int i;

	switch( mode )
	{
	case N_DOT_L:
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )
		{
			float red, green, blue;
			float sum;

			red = (saturate(dot( data[i], red_vector )));
			green = (saturate(dot( data[i], green_vector )));
			blue = (saturate(dot( data[i], blue_vector )));

			data[i].x = red;
			data[i].y = green;
			data[i].z = blue;

			sum = dot( data[i], make_float3(1.0f, 1.0f, 1.0f) );
			data[i].x /= sum;
			data[i].y /= sum;
			data[i].z /= sum;
		}
		break;
	case N_DOT_L2:
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )
		{
			float temp;
			float3 normal;
			float sum;

			normal = data[i];

			temp = saturate(dot( normal, red_vector ));
			data[i].x = temp * temp;

			temp = saturate(dot( normal, green_vector ));
			data[i].y = temp * temp;

			temp = saturate(dot( normal, blue_vector ));
			data[i].z = temp * temp;

			sum = dot( data[i], make_float3(1.0f, 1.0f, 1.0f) );
			data[i].x /= sum;
			data[i].y /= sum;
			data[i].z /= sum;
		}
		break;

	case N_DOT_L4:
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )
		{
			float temp;
			float3 normal;

			normal = data[i];
			
			temp =  1 - saturate(dot( normal, red_vector ));
			temp = temp * temp;
			temp *= temp;
			data[i].x = 1 - temp;

			temp =  1 - saturate(dot( normal, green_vector ));
			temp = temp * temp;
			temp *= temp;
			data[i].y = 1 - temp;

			temp =  1 - saturate(dot( normal, blue_vector ));
			temp = temp * temp;
			temp *= temp;
			data[i].z = 1 - temp;
		}
		break;
	}
}

//Algorithm from http://www.modwiki.net/wiki/Start_a_Specular_map_with_a_Normal_map
//Lighten_only blend from http://gimp-savvy.com/BOOK/index.html?node55.html
void Normal2Specular(unsigned char *data, int height, int width)
{
	int i;

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		int pos;
		unsigned char temp;

		pos = i * 3;

		temp = 128;

		temp = MAX( temp, data[pos] );
		temp = MAX( temp, (255 - data[pos]) );
		temp = MAX( temp, data[pos + 1] );
		temp = MAX( temp, (255 - data[pos + 1]) );

		data[pos] = data[pos + 1] = data[pos + 2] = temp;
	}
}

//Algorithm from http://www.modwiki.net/wiki/Start_a_Specular_map_with_a_Normal_map
//Lighten_only blend from http://gimp-savvy.com/BOOK/index.html?node55.html
void Normal2Specular(float3 *data, int height, int width)
{
	int i;

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		float temp;

		temp = 0.5f;

		data[i].x = (data[i].x + 1.0f) / 2;
		data[i].y = (data[i].y + 1.0f) / 2;

		temp = MAX( temp, data[i].x );
		temp = MAX( temp, (1.0f - data[i].x) );
		temp = MAX( temp, data[i].y );
		temp = MAX( temp, (1.0f - data[i].y) );

		data[i].x = data[i].y = data[i].z = temp;
	}
}

//Modified from code from ATI
void Normal2DuDv( unsigned char *data, int height, int width )
{
	#pragma omp parallel for
	for( int i = 0; i < height * width; i++ )
	{
		int pos;

		pos = i * 3;

		data[pos] = (unsigned char)((int)data[i * 3] - 127);
		data[pos + 1] = (unsigned char)((int)data[i * 3 + 1] - 127);
		data[pos + 2] = 0;
	}
}

//Modified from code from ATI
void Normal2DuDv( float3 *data, int height, int width )
{
	#pragma omp parallel for
	for( int i = 0; i < height * width; i++ )
	{
		data[i].x = (data[i].x + 1.0f) / 2;
		data[i].y = (data[i].y + 1.0f) / 2;

		data[i].x = data[i].x - 0.5f;
		data[i].y = data[i].y - 0.5f;
		data[i].z = 0;
	}
}

void Image2Height( unsigned char *data, int height, int width)
{

}

void Height2Normal( unsigned char *data, int height, int width, float scale)
{
	int i;
	float  *h = new float[height * width];

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
		h[i] = ((int)data[i * 3] + (int)data[i * 3 + 1] + (int)data[i * 3 + 2]) / 765.0f * scale;

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		float3  normal;
		int col, row, pos;
		int left, right, up, down;

		row = i / width;
		col = i % width;

		left = col - 1;
		right = col + 1;
		up = row - 1;
		down = row + 1;

		if( left < 0 )
			left = width - 1;
		else if( right >= width )
			right = 0;

		if( up < 0 )
			up = height - 1;
		else if( down >= height )
			down = 0;

		normal = GetNormal( h[down * width + col], h[up * width + col], h[row * width + right], h[row * width + left] );

		pos = i * 3;
		data[i]     = (unsigned char)((normal.x + 1.0f) * 127.5f);
		data[i + 1] = (unsigned char)((normal.y + 1.0f) * 127.5f);
		data[i + 2] = (unsigned char)((normal.z + 1.0f) * 127.5f);
	}

	delete [] h;
}

void Height2Normal( float3 *data, int height, int width, float scale)
{
	int i;
	float  *h = new float[height * width];

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
		h[i] = (data[i].x + data[i].y + data[i].z) / 3.0f * scale;

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		int col, row;
		int left, right, up, down;

		row = i / width;
		col = i % width;

		left = col - 1;
		right = col + 1;
		up = row - 1;
		down = row + 1;

		if( left < 0 )
			left = width - 1;
		else if( right >= width )
			right = 0;

		if( up < 0 )
			up = height - 1;
		else if( down >= height )
			down = 0;

		data[i] = GetNormal( h[down * width + col], h[up * width + col], h[row * width + right], h[row * width + left] );
	}

	delete [] h;
}

void Height2Normal( float *h, float3 *dest, int height, int width )
{
	int i;

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		int col, row;
		int left, right, up, down;

		row = i / width;
		col = i % width;

		left = col - 1;
		right = col + 1;
		up = row - 1;
		down = row + 1;

		if( left < 0 )
			left = width - 1;
		else if( right >= width )
			right = 0;

		if( up < 0 )
			up = height - 1;
		else if( down >= height )
			down = 0;

		dest[i] = GetNormal( h[down * width + col], h[up * width + col], h[row * width + right], h[row * width + left] );
	}
}

/*
void NormalIntensity( float3 *normal, int height, int width, float intensity, int thread_id, int processors )
{
	int i;

	if( intensity >= 2.0f || intensity <= -2.0f )
		return;

	if( intensity == 0.0f )
	{
		for( i = 0; i < height * width; i++ )
		{
			normal[i].x = 0;
			normal[i].y = 0;
			normal[i].z = 1.0f;

			normal[i] = normalize( normal[i] );
		}
		return;
	}


	if( intensity > 1.0f || intensity < -1.0f )
	{
		if( intensity > 0 )
		{
			intensity -= 1.0f;
			intensity = 1.0f - intensity;
			for( i = 0; i < height * width; i++ )
			{
				normal[i].z *= intensity;

				normal[i] = normalize( normal[i] );
			}
		}
		else
		{
			intensity += 1.0f;
			intensity *= -1;
			intensity = 1.0f - intensity;
			for( i = 0; i < height * width; i++ )
			{
				normal[i].x *= -1;
				normal[i].y *= -1;
				normal[i].z *= intensity;

				normal[i] = normalize( normal[i] );
			}
		}
	}
	else
	{
		if( intensity > 0 )
		{
			intensity = 1.0f - intensity;
			intensity *= 8.0f;
			intensity = 1.0f + intensity;
			for( i = 0; i < height * width; i++ )
			{
				normal[i].z *= intensity;

				normal[i] = normalize( normal[i] );
			}
		}
		else
		{
			intensity *= -1;
			intensity = 1.0f - intensity;
			intensity *= 8.0f;
			intensity = 1.0f + intensity;
			for( i = 0; i < height * width; i++ )
			{
				normal[i].x *= -1;
				normal[i].y *= -1;
				normal[i].z *= intensity;

				normal[i] = normalize( normal[i] );
			}
		}
	}
} */

void NormalScale( float3 *normal, int height, int width, float intensity )
{
	int i;

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		normal[i].x *= intensity;
		normal[i].y *= intensity;

		normal[i] = normalize(normal[i]);
	}
}

void NormalEdges( float3 *normal, float *h, int height, int width, float strength, float intensity )
{
	float *temp = new float[height * width];
//	int row, col;
//	int right, left, up, down;
	int i;

	if( intensity < 0.0f )
		intensity = 0.0f;
	else if( intensity > 1.0f )
		intensity = 1.0f;

/*	for( i = thread_id; i < height * width; i += processors )
	{
		row = i / width;
		col = i % width;

		right = col + 1;
		left = col - 1;
		up = row - 1;
		down = row + 1;

		if( left < 0 )
			left = width - 1;
		else if( right >= width )
			right = 0;

		if( up < 0 )
			up = height - 1;
		else if( down >= height )
			down = 0;

		temp[row * width + col] = 1.0f - ComputeSobel( h[up * width + left], h[up * width + col],
			                                           h[up * width + right], h[row * width + left],
										    		   h[row * width + col], h[row * width + right],
											           h[down * width + left], h[down * width + col],
												       h[down * width + right], strength );
	} */

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		float temp_f;

		temp_f = 0.0f;

		temp_f = MAX( temp_f, ABS(normal[i].x) );
		temp_f = MAX( temp_f, ABS(normal[i].y) );

		temp[i] = 1.0f - MIN(temp_f * strength, 1.0f);
	}

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		normal[i].z *= ( MAX( 0.01f, MIN( temp[i] + (1.0f - intensity), 1.0f )) );

		normal[i] = normalize( normal[i] );
	}

	delete [] temp;
}

void GenerateRays( int height, int width, ray* &red, ray* &blue, ray* &green, int rays, float theta_limit, float alpha_limit )
{
	//float3 green_vector = make_float3((float)(-rsqrt(6.0f)), (float)(rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 blue_vector = make_float3((float)(-rsqrt(6.0f)), (float)(-rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 red_vector = make_float3((float)(sqrt(2.0f)/sqrt(3.0f)), 0.0f, (float)(rsqrt(3.0f)));

	float3 green_light = make_float3( -0.40824829f, -0.70710678f, 0.57735027f );
	float3 blue_light  = make_float3( -0.40824829f,  0.70710678f, 0.57735027f );
//	float3 red_light   = make_float3(  0.92210791f,  0.00000000f, 0.57735027f );
	float3 red_light   = make_float3(  0.81649658f,  0.00000000f, 0.57735027f );

	float min, max, min2, max2;
	float pixel_width = 1.0f / width;
	int i;

        srand((unsigned)time(NULL));

	min = 35.264338968f - alpha_limit / 2.0f;
	if( min < 0.0f )
		min = 0.0f;
		
	max = 35.264338968f + alpha_limit / 2.0f;
	if( max > 90.0f )
		max = 90.0f; 
		
	min2 = 25.239440187f - alpha_limit / 2.0f;
	if( min2 < 0.0f )
		min2 = 0.0f;
		
	max2 = 25.239440187f + alpha_limit / 2.0f;
	if( max2 > 90.0f )
		max2 = 90.0f; 

	//Randomly generate arrays within specified bounds
	#pragma omp parallel for
	for( i = 0; i < rays; i++)
	{		
		float deg_alpha, theta;
		float x_inc, y_inc, z_inc;

		if( i == 0 )
		{
			//set first ray to light vector
			red[i].x = ( red_light.x > 0? (pixel_width) : (-pixel_width));
			red[i].y = red[i].x * red_light.y / red_light.x * height;
			red[i].z = red[i].x * red_light.z / red_light.x;
			red[i].x *= width;

			red[i + rays].x = red_light.x;
			red[i + rays].y = red_light.y;
			red[i + rays].z = red_light.z;

			green[i].x = ( green_light.x > 0? (pixel_width) : (-pixel_width));
			green[i].y = green[i].x * green_light.y / green_light.x * height;
			green[i].z = green[i].x * green_light.z / green_light.x;
			green[i].x *= width;

			green[i + rays].x = green_light.x;
			green[i + rays].y = green_light.y;
			green[i + rays].z = green_light.z;

			blue[i].x = ( blue_light.x > 0? (pixel_width) : (-pixel_width));
			blue[i].y = blue[i].x * blue_light.y / blue_light.x * height;
			blue[i].z = blue[i].x * blue_light.z / blue_light.x;
			blue[i].x *= width;

			blue[i + rays].x = blue_light.x;
			blue[i + rays].y = blue_light.y;
			blue[i + rays].z = blue_light.z;
		}
		else
		{
			//Randomly generate rays within specified bounds
                        deg_alpha = min + (float)((max - min) * ((double)rand() / (double)RAND_MAX));

                        theta = (theta_limit / -2.0f) + (float)(theta_limit * ((double)rand() / (double)RAND_MAX));

			blue[i + rays].x = cos(torad(deg_alpha)) * cos(torad(120.0f + theta));
			blue[i + rays].y = cos(torad(deg_alpha)) * sin(torad(120.0f + theta));
			blue[i + rays].z = sin(torad(deg_alpha));

			x_inc = (blue[i + rays].x > 0? (pixel_width) : (-pixel_width));
			y_inc = (x_inc * blue[i + rays].y) / blue[i + rays].x;
			z_inc = (x_inc * blue[i + rays].z) / blue[i + rays].x;

			//Store slope in pixels
			blue[i].x = x_inc * width;
			blue[i].y = y_inc * height;
			blue[i].z = z_inc;

			green[i + rays].x = cos(torad(deg_alpha)) * cos(torad(240.0f + theta));
			green[i + rays].y = cos(torad(deg_alpha)) * sin(torad(240.0f + theta));
			green[i + rays].z = sin(torad(deg_alpha));

			x_inc = (green[i + rays].x > 0? (pixel_width) : (-pixel_width));
			y_inc = (x_inc * green[i + rays].y) / green[i + rays].x;
			z_inc = (x_inc * green[i + rays].z) / green[i + rays].x;

			//Store slope in pixels
			green[i].x = x_inc * width;
			green[i].y = y_inc * height;
			green[i].z = z_inc;
		
			if( deg_alpha < min2 || deg_alpha > max2 )
			{
                                deg_alpha = min2 + (float)((max2 - min2) * ((double)rand() / (double)RAND_MAX));
			}

			red[i + rays].x = sqrt(11.0f/6.0f) * cos(torad(deg_alpha)) * cos(torad(theta));
			red[i + rays].y = sqrt(11.0f/6.0f) * cos(torad(deg_alpha)) * sin(torad(theta));
			red[i + rays].z = sqrt(11.0f/6.0f) * sin(torad(deg_alpha));

			x_inc = (red[i + rays].x > 0? (pixel_width) : (-pixel_width));
			y_inc = (x_inc * red[i + rays].y) / red[i + rays].x;
			z_inc = (x_inc * red[i + rays].z) / red[i + rays].x;

			//Store slope in pixels
			red[i].x = x_inc * width;
			red[i].y = y_inc * height;
			red[i].z = z_inc;
		}
	}
}

float trace_rays(float* h, int height, int width, int row, int col, int rays, 
				 float h_scale, float max_height, float radius, ray* ray,
				 int max_dist, bool tile, bool h_tile, bool v_tile)
{
	bool unoccluded = true;

	float z = h[row * width + col];
	radius += z;
	if( z == max_height)
		return 1.0f;
	if( radius < max_height )
		max_height = radius;
	float z2;
	int row2, col2;
	float row2_f, col2_f;
	int i, r;
	float unoccluded_rays = 0.0f;

    for( r = 0; r < rays; r++) 
	{
		unoccluded = true;
		i = 0;
		
		z2 = z;
		row2_f = (float)row;
		col2_f = (float)col;

		do
		{
			z2 += ray[r].z;

			row2_f += ray[r].y;
			row2 = (int)(row2_f + 0.5f);

			if( row2 - row > max_dist || row2 - row < -max_dist)
				break;
			if( (!tile || !v_tile) && (row2 > height || row2 < 0) )
				break;

			limit_num(row2, height - 1);

			col2_f += ray[r].x;
			col2 = (int)(col2_f + 0.5f);

			if( (!tile || !h_tile) && (col2 > width || col2 < 0) )
				break;

			limit_num(col2, width - 1);

			if( h[row2 * width + col2] >= z2 )
			{
				unoccluded = false;
				break;
			}

			i++;
		}while(z2 < max_height && i < max_dist);

		if(unoccluded)
			unoccluded_rays++;
    }

	return unoccluded_rays / rays;
}

void Height2DirectionalAO( unsigned char *data, float* h, int height, int width,
						   ray* red, ray* blue, ray* green, int rays, float scale,
						   float radius, bool tile, bool h_tile, bool v_tile, int* complete )
{
	long pos, i;
	float max_height_val = 0.0f;
	int max_dist = (int)(radius * width + 0.5f);
	int temp;

	temp = 0;
	int processors = omp_get_num_procs();

	if( complete == NULL )
		complete = &temp;

	//Find highest point
	for( i = 0; i < height * width; i++ )
	{
		if( h[i] > max_height_val )
			max_height_val = h[i];
		else if( max_height_val == 1.0f )
			break;
	}

	i = 0;
	//Start processing image
	#pragma omp parallel for
	for( pos = 0; pos < height * width; pos++)
	{
		int row, col;
		long px;
		float shadow;

		col = pos % width;
	    row = pos / width;
		px = pos * 3;

		//Calculate Red Color
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, red, max_dist, tile, h_tile, v_tile);
		shadow = saturate(shadow);
		data[px] = (unsigned char)(shadow * 255.0f); 

		//Calculate Green value
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, green, max_dist, tile, h_tile, v_tile);		
		shadow = saturate(shadow);
		data[px + 1] = (unsigned char)(shadow * 255.0f);

		//Calculate Blue Color
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, blue, max_dist, tile, h_tile, v_tile);
		shadow = saturate(shadow);
		data[px + 2] = (unsigned char)(shadow * 255.0f);
	
		if( omp_get_thread_num() == 0 )
		{
			i++;
			if(i%(height*width/(100*processors)) == 0)
			{
				//Update Status
				*complete = (int)((float)i * processors / (height * width) * 1000);
			}
		}
	}
}

void ChangeDepth(float * h, int height, int width, float amount, float scale)
{
	int i;
	float mid = 0.5f * scale;

	#pragma omp parallel for
	for(i = 0; i < width * height; i++)
		h[i] = h[i] + ((h[i] - mid) * amount);
}

void Contrast(float * data, int height, int width, float contrast)
{
	int i;

	#pragma omp parallel for
	for(i = 0; i < width * height; i++)
		data[i] = saturate(data[i] + ((data[i] - 0.5f) * contrast));
}

void Height2DirectionalAO( float3 *data, float* h, int height, int width,
						   ray* red, ray* blue, ray* green, int rays, float scale,
						   float radius, bool tile, bool h_tile, bool v_tile, int* complete )
{
	long pos, i;
	float max_height_val = 0.0f;
	int max_dist = (int)(radius * width + 0.5f);
	int temp;

	temp = 0;

    int processors = omp_get_num_procs();

	if( complete == NULL )
		complete = &temp;

	//Find highest point
	for( i = 0; i < height * width; i++ )
	{
		if( h[i] > max_height_val )
			max_height_val = h[i];
		else if( max_height_val == 1.0f )
			break;
	}

	i = 0;
	//Start processing image
	#pragma omp parallel for schedule( guided, 1 )
	for( pos = 0; pos < height * width; pos++)
	{
		float shadow;
		int row, col;

		col = pos % width;
	    row = pos / width;

		//Calculate Red Color
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                    scale, radius, red, max_dist, tile, h_tile, v_tile);
		data[pos].x = saturate(shadow);

		//Calculate Green value
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                    scale, radius, green, max_dist, tile, h_tile, v_tile);		
		data[pos].y = saturate(shadow);

		//Calculate Blue Color
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                    scale, radius, blue, max_dist, tile, h_tile, v_tile);
		data[pos].z = saturate(shadow);
	
		if( omp_get_thread_num() == 0 )
		{
			i++;
			if(i%(height*width/(100*processors)) == 0)
			{
				//Update Status
				*complete = (int)((float)i * processors / (height * width) * 1000);
			}
		}
	}
}

void BlendNormal( float percent, float3 *src1, float3 *src2, float3 *dest, int height, int width)
{
	int i;

	if( percent >= 100.0f )
		percent = 1.0f;
	else if( percent < 0.0f )
		percent = 0.0f;
	else
		percent /= 100.0f;

	#pragma omp parallel for
	for( i = 0; i < height * width; i++ )
	{
		float3 n1, n2, n3;

		n1 = ret_deriv( src1[i] );
		n2 = ret_deriv( src2[i] );

		n3.x = n2.x * percent + n1.x * (1 - percent);
		n3.y = n2.y * percent + n1.y * (1 - percent);
		n3.z = n2.z * percent + n1.z * (1 - percent);

		dest[i] = normalize(n3);
	}
}

//Equations From
//Grokking the GIMP
//By Carey Bunks
//http://gimp-savvy.com/BOOK/index.html?node55.html
void Blend( BlendType type, float percent, unsigned char *src, unsigned char *src2, unsigned char *dest, int height, int width)
{
	int i, j;
	unsigned char temp_c;
	float temp1, temp2, screen, result;
	float r, g, b;
	float hue, saturation, value, lightness;
	int h;
	float min, max;
	float f, p, q, t, h_f;
	float pixel[3] = {0.0f};

	if( percent >= 100.0f )
		percent = 1.0f;
	else if( percent < 0.0f )
		percent = 0.0f;
	else
		percent /= 100.0f;

	switch( type )
	{
	case DEFAULT:
		//Modified from code
		//Copyright (c) Alex Cornejo
		//http://people.csail.mit.edu/acornejo/html/blender.htm
		#pragma omp parallel for
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + src[i] * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + src[i + 1] * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + src[i + 2] * percent);
		}
		break;

	case OVERLAY:
		#pragma omp parallel for private(temp1, temp2, screen, result)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			temp1 = src2[i] / 255.0f;
			temp2 = src[i] / 255.0f;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i] = (unsigned char)((temp1 * (1.0f - percent) + result * percent) * 255);

			temp1 = src2[i + 1] / 255.0f;
			temp2 = src[i + 1] / 255.0f;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i + 1] = (unsigned char)((temp1 * (1.0f - percent) + result * percent) * 255);

			temp1 = src2[i + 2] / 255.0f;
			temp2 = src[i + 2] / 255.0f;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i + 2] = (unsigned char)((temp1 * (1.0f - percent) + result * percent) * 255);
		}
		break;

	case SCREEN:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			//temp_c = ~(unsigned char)(((int)(~src[i]) * ~src2[i]) >> 8);
			temp_c = 255 - (((255 - (int)src[i]) * (255 - (int)src2[i])) >> 8);
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			//temp_c = ~(unsigned char)(((int)(~src[i + 1]) * ~src2[i + 1]) >> 8);
			temp_c = 255 - (((255 - (int)src[i + 1]) * (255 - (int)src2[i + 1])) >> 8);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			//temp_c = ~(unsigned char)(((int)(~src[i + 2]) * ~src2[i + 2]) >> 8);
			temp_c = 255 - (((255 - (int)src[i + 2]) * (255 - (int)src2[i + 2])) >> 8);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case LIGHTEN:
		#pragma omp parallel for
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + MAX( src2[i], src[i] ) * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + MAX( src2[i + 1], src[i + 1] ) * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + MAX( src2[i + 2], src[i + 2] ) * percent);
		}
		break;

	case DARKEN:
		#pragma omp parallel for
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + MIN( src2[i], src[i] ) * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + MIN( src2[i + 1], src[i + 1] ) * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + MIN( src2[i + 2], src[i + 2] ) * percent);
		}
		break;

	case MULTIPLY:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			temp_c = (unsigned char)(((int)src2[i] * src[i]) >> 8);
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)(((int)src2[i + 1] * src[i + 1]) >> 8);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)(((int)src2[i + 2] * src[i + 2]) >> 8);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case DIVIDE:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			temp_c = (unsigned char)( MIN(255, ((int)src2[i] << 8) / ((int)src[i] + 1) ) );
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MIN(255, ((int)src2[i + 1] << 8) / ((int)src[i + 1] + 1) ) );
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MIN(255, ((int)src2[i + 2] << 8) / ((int)src[i + 2] + 1) ) );
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case ADDITION:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			temp_c = (unsigned char)( MIN( (int)src[i] + (int)src2[i], 255 ) );
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MIN( (int)src[i + 1] + (int)src2[i + 1], 255 ) );
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MIN( (int)src[i + 2] + (int)src2[i + 2], 255 ) );
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case SUBTRACTION:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			temp_c = (unsigned char)( MAX( (int)src2[i] - (int)src[i], 0 ) );
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MAX( (int)src2[i + 1] - (int)src[i + 1], 0 ) );
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MAX( (int)src2[i + 2] - (int)src[i + 2], 0 ) );
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case DIFF:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			temp_c = (unsigned char)( ABS( (int)src2[i] - (int)src[i] ) );
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( ABS( (int)src2[i + 1] - (int)src[i + 1] ) );
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( ABS( (int)src2[i + 2] - (int)src[i + 2] ) );
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case HUE:
		//Hue, Saturation, Value Equations from Wikipedia
		//http://en.wikipedia.org/wiki/HSL_and_HSV#Formal_specifications
		#pragma omp parallel for private(r, g, b, max, min, hue, saturation, value, h, f, t, p, q)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			//Convert RGB to HSV
			r = src[i] / 255.0f;
			g = src[i + 1] / 255.0f;
			b = src[i + 2] / 255.0f;

			max = MAX3(r, g, b);
			min = MAX3(r, g, b);

			if( max == min )
				hue = 0;
			else if( max == r )
				hue = (float)((int)(60 * (g - b) / (max - min) + 360) % 360);
			else if( max == g)
				hue = 60 * (b - r) / (max - min) + 120;
			else //max == b
				hue = 60 * (r - g) / (max - min) + 240;

			r = src2[i] / 255.0f;
			g = src2[i + 1] / 255.0f;
			b = src2[i + 2] / 255.0f;

			if( MAX3(r, g, b) == 0 )
				saturation = 0.0f;
			else
				saturation = 1.0f - (MIN3(r, g, b)/MAX3(r, g, b));
			value = MAX3(r, g, b);

			//Convert HSV to RGB
			h = (int)(hue / 60) % 6;
			f = hue/60 - (int)hue/60;
			p = value * (1 - saturation);
			q = value * (1 - (f * saturation));
			t = value * (1 - ((1 - f) * saturation));

			switch( h )
			{
			case 0:
				//v,t,p
				r = value * 255;
				g = t * 255;
				b = p * 255;
				break;

			case 1:
				//q,v,p
				r = q * 255;
				g = value * 255;
				b = p * 255;
				break;

			case 2:
				//p,v,t
				r = p * 255;
				g = value * 255;
				b = t * 255;
				break;

			case 3:
				//p,q,v
				r = p * 255;
				g = q * 255;
				b = value * 255;
				break;

			case 4:
				//t,p,v
				r = t * 255;
				g = p * 255;
				b = value * 255;
				break;

			case 5:
				//v,p,q
				r = value * 255;
				g = p * 255;
				b = q * 255;
				break;
			}

			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + r * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + g * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + b * percent);
		}
		break;

	case SATURATION:
		//Hue, Saturation, Value Equations from Wikipedia
		//http://en.wikipedia.org/wiki/HSL_and_HSV#Formal_specifications
		#pragma omp parallel for private(r, g, b, max, min, hue, saturation, value, h, f, t, p, q)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			//Convert RGB to HSV
			r = src2[i] / 255.0f;
			g = src2[i + 1] / 255.0f;
			b = src2[i + 2] / 255.0f;

			max = MAX3(r, g, b);
			min = MAX3(r, g, b);

			if( max == min )
				hue = 0;
			else if( max == r )
				hue = (float)((int)(60 * (g - b) / (max - min) + 360) % 360);
			else if( max == g)
				hue = 60 * (b - r) / (max - min) + 120;
			else //max == b
				hue = 60 * (r - g) / (max - min) + 240;

			value = MAX3(r, g, b);

			r = src[i] / 255.0f;
			g = src[i + 1] / 255.0f;
			b = src[i + 2] / 255.0f;

			saturation = 1.0f - (MIN3(r, g, b)/MAX3(r, g, b));

			//Convert HSV to RGB
			h = (int)(hue / 60) % 6;
			f = hue/60 - (int)hue/60;
			p = value * (1 - saturation);
			q = value * (1 - f * saturation);
			t = value * (1 - (1 - f) * saturation);

			switch( h )
			{
			case 0:
				//v,t,p
				r = value * 255;
				g = t * 255;
				b = p * 255;
				break;

			case 1:
				//q,v,p
				r = q * 255;
				g = value * 255;
				b = p * 255;
				break;

			case 2:
				//p,v,t
				r = p * 255;
				g = value * 255;
				b = t * 255;
				break;

			case 3:
				//p,q,v
				r = p * 255;
				g = q * 255;
				b = value * 255;
				break;

			case 4:
				//t,p,v
				r = t * 255;
				g = p * 255;
				b = value * 255;
				break;

			case 5:
				//v,p,q
				r = value * 255;
				g = p * 255;
				b = q * 255;
				break;
			}

			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + r * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + g * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + b * percent);
		}
		break;

	case VALUE:
		//Hue, Saturation, Value Equations from Wikipedia
		//http://en.wikipedia.org/wiki/HSL_and_HSV#Formal_specifications
		#pragma omp parallel for private(r, g, b, max, min, hue, saturation, value, h, f, t, p, q)
		for( i = 0; i < height * width * 3; i += 3)	
		{
			//Convert RGB to HSV
			r = src2[i] / 255.0f;
			g = src2[i + 1] / 255.0f;
			b = src2[i + 2] / 255.0f;

			max = MAX3(r, g, b);
			min = MAX3(r, g, b);

			if( max == min )
				hue = 0;
			else if( max == r )
				hue = (float)((int)(60 * (g - b) / (max - min) + 360) % 360);
			else if( max == g)
				hue = 60 * (b - r) / (max - min) + 120;
			else //max == b
				hue = 60 * (r - g) / (max - min) + 240;

			saturation = 1.0f - (MIN3(r, g, b)/MAX3(r, g, b));

			r = src[i] / 255.0f;
			g = src[i + 1] / 255.0f;
			b = src[i + 2] / 255.0f;

			value = MAX3(r, g, b);

			//Convert HSV to RGB
			h = (int)(hue / 60) % 6;
			f = hue/60 - (int)hue/60;
			p = value * (1 - saturation);
			q = value * (1 - f * saturation);
			t = value * (1 - (1 - f) * saturation);

			switch( h )
			{
			case 0:
				//v,t,p
				r = value * 255;
				g = t * 255;
				b = p * 255;
				break;

			case 1:
				//q,v,p
				r = q * 255;
				g = value * 255;
				b = p * 255;
				break;

			case 2:
				//p,v,t
				r = p * 255;
				g = value * 255;
				b = t * 255;
				break;

			case 3:
				//p,q,v
				r = p * 255;
				g = q * 255;
				b = value * 255;
				break;

			case 4:
				//t,p,v
				r = t * 255;
				g = p * 255;
				b = value * 255;
				break;

			case 5:
				//v,p,q
				r = value * 255;
				g = p * 255;
				b = q * 255;
				break;
			}

			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + r * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + g * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + b * percent);
		}
		break;

	case COLOR:
		//Hue, Saturation, Value Equations from Wikipedia
		//http://en.wikipedia.org/wiki/HSL_and_HSV#Formal_specifications
		#pragma omp parallel for private(r, g, b, max, min, hue, saturation, p, q)
		for( i = 0; i < height * width * 3; i += 3 )	
		{
			//Convert RGB to HSL
			r = src[i] / 255.0f;
			g = src[i + 1] / 255.0f;
			b = src[i + 2] / 255.0f;

			max = MAX3(r, g, b);
			min = MAX3(r, g, b);

			if( max == min )
				hue = 0;
			else if( max == r )
				hue = (float)((int)(60 * (g - b) / (max - min) + 360) % 360);
			else if( max == g)
				hue = 60 * (b - r) / (max - min) + 120;
			else //max == b
				hue = 60 * (r - g) / (max - min) + 240;

			lightness = 0.5f * (MIN3(r, g, b) + MAX3(r, g, b));

			if( max == min )
				saturation = 0.0f;
			else if( lightness <= 0.5f )
				saturation = (max - min) / (2 * lightness);
			else //lightness > 0.5f
				saturation = (max - min) / (2 - 2 * lightness);

			r = src2[i] / 255.0f;
			g = src2[i + 1] / 255.0f;
			b = src2[i + 2] / 255.0f;

			lightness = 0.5f * (MIN3(r, g, b) + MAX3(r, g, b));

			//Convert HSL to RGB
			if( saturation == 0.0f )
			{
				pixel[RED] = pixel[GREEN] = pixel[BLUE] = lightness;
			}
			else
			{
				if( lightness < 0.5f )
					q = lightness * (1 + saturation);
				else
					q = lightness + saturation - lightness * saturation;

				p = 2 * lightness - q ;
				h_f = height / 360.0f;

				pixel[RED] = h_f + 1.0f/3.0f;
				if( pixel[RED] < 0 )
					pixel[RED] += 1.0f;
				else if( pixel[RED] > 1.0f )
					pixel[RED] -= 1.0f;

				pixel[GREEN] = h_f;
				if( pixel[GREEN] < 0 )
					pixel[GREEN] += 1.0f;
				else if( pixel[GREEN] > 1.0f )
					pixel[GREEN] -= 1.0f;

				pixel[BLUE] = h_f - 1.0f/3.0f;
				if( pixel[BLUE] < 0 )
					pixel[BLUE] += 1.0f;
				else if( pixel[BLUE] > 1.0f )
					pixel[BLUE] -= 1.0f;

				for( j = 0; j < 3; j++ )
				{
					if( pixel[j] < 1.0f/6.0f )
						pixel[j] = p + ((q - p) * 6 * pixel[j]);
					else if( pixel[j] < 0.5f )
						pixel[j] = q;
					else if( pixel [j] < 2.0f/3.0f )
						pixel[j] = p + ((q - p) * 6 * (2.0f/3.0f - pixel[j]));
					else
						pixel[j] = p;
				}
			}

			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + pixel[RED] * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + pixel[GREEN] * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + pixel[BLUE] * percent);
		}
		break;
	}
}

void Blend( BlendType type, float percent, float3 *src2, float3 *src, float3 *dest, int height, int width )
{
	int i;
	float temp_c;
	float temp1, temp2, screen, result;

	if( percent >= 100.0f )
		percent = 1.0f;
	else if( percent < 0.0f )
		percent = 0.0f;
	else
		percent /= 100.0f;

	switch( type )
	{
	case DEFAULT:
		//Modified from code
		//Copyright (c) Alex Cornejo
		//http://people.csail.mit.edu/acornejo/html/blender.htm
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )	
		{
			dest[i].x = src2[i].x * (1.0f - percent) + src[i].x * percent;
			dest[i].y = src2[i].y * (1.0f - percent) + src[i].y * percent;
			dest[i].z = src2[i].z * (1.0f - percent) + src[i].z * percent;
		}
		break;

	case OVERLAY:
		#pragma omp parallel for private(temp1, temp2, screen, result)
		for( i = 0; i < height * width; i++ )		
		{
			temp1 = src2[i].x;
			temp2 = src[i].x;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i].x = temp1 * (1.0f - percent) + result * percent;

			temp1 = src2[i].y;
			temp2 = src[i].y;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i].y = temp1 * (1.0f - percent) + result * percent;

			temp1 = src2[i].z;
			temp2 = src[i].z;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i].z = temp1 * (1.0f - percent) + result * percent;
		}
		break;

	case SCREEN:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width; i++ )	
		{
			temp_c = 1.0f - (1.0f - src[i].x) * (1.0f - src2[i].x);
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = 1.0f - (1.0f - src[i].y) * (1.0f - src2[i].y);
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = 1.0f - (1.0f - src[i].z) * (1.0f - src2[i].z);
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case LIGHTEN:
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )	
		{
			dest[i].x = src2[i].x * (1.0f - percent) + MAX( src2[i].x, src[i].x ) * percent;
			dest[i].y = src2[i].y * (1.0f - percent) + MAX( src2[i].y, src[i].y ) * percent;
			dest[i].z = src2[i].z * (1.0f - percent) + MAX( src2[i].z, src[i].z ) * percent;
		}
		break;

	case DARKEN:
		#pragma omp parallel for
		for( i = 0; i < height * width; i++ )	
		{
			dest[i].x = src2[i].x * (1.0f - percent) + MIN( src2[i].x, src[i].x ) * percent;
			dest[i].y = src2[i].y * (1.0f - percent) + MIN( src2[i].y, src[i].y ) * percent;
			dest[i].z = src2[i].z * (1.0f - percent) + MIN( src2[i].z, src[i].z ) * percent;
		}
		break;

	case MULTIPLY:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width; i++ )	
		{
			temp_c = src2[i].x * src[i].x;
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = src2[i].y * src[i].y;
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = src2[i].z * src[i].z;
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case DIVIDE:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width; i++ )	
		{
			temp_c = MIN(1.0f, src2[i].x / MAX(0.0039215f, src[i].x + 1) );
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = MIN(1.0f, src2[i].x / MAX(0.0039215f, src[i].y + 1) );
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = MIN(1.0f, src2[i].x / MAX(0.0039215f, src[i].z + 1) );
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case ADDITION:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width; i++ )	
		{
			temp_c = MIN( src[i].x + src2[i].x, 1.0f );
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = MIN( src[i].y + src2[i].y, 1.0f ) ;
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = MIN( src[i].z + src2[i].z, 1.0f ) ;
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case SUBTRACTION:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width; i++ )	
		{
			temp_c = MAX( src2[i].x - src[i].x, 0 );
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = MAX( src2[i].y - src[i].y, 0 );
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = MAX( src2[i].z - src[i].z, 0 );
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case DIFF:
		#pragma omp parallel for private(temp_c)
		for( i = 0; i < height * width; i++ )
		{
			temp_c = ABS( src2[i].x - src[i].x );
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = ABS( src2[i].y - src[i].y );
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = ABS( src2[i].z - src[i].z );
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;
        case SATURATION:
        case VALUE:
        case COLOR:
        case HUE:
                break;
	}
}

void NormalOverlay( float3* src1, float3* src2, float3* dest, float* h1, float* h2, int height, int width )
{
	int i;

	float3 n1, n2, n3;

	#pragma omp parallel for private(n1, n2, n3)
	for( i = 0; i < height * width; i++ )
	{
		n1 = ret_deriv( src1[i] );
		n2 = ret_deriv( src2[i] );

		n3.x = n2.x - 2*h2[i]*n2.x + n1.x*h2[i]*h2[i]*h2[i] + 3*h2[i]*h2[i]*n2.x*h1[i] + n1.x*h2[i] + n2.x*h1[i] - 2*n1.x*h2[i]*h2[i] + 4*h2[i]*n2.x*h1[i];
		n3.y = n2.y - 2*h2[i]*n2.y + n1.y*h2[i]*h2[i]*h2[i] + 3*h2[i]*h2[i]*n2.y*h1[i] + n1.y*h2[i] + n2.y*h1[i] - 2*n1.y*h2[i]*h2[i] + 4*h2[i]*n2.y*h1[i];
		n3.z = 1;

		dest[i] = normalize(n3);
	}
}

void NormalModulation( float3* src1, float3* src2, float3* dest, float* h1, float* h2, int height, int width )
{
	int i;

	float3 n1, n2, n3;

	#pragma omp parallel for private(n1, n2, n3)
	for( i = 0; i < height * width; i++ )
	{
		n1 = ret_deriv( src1[i] );
		n2 = ret_deriv( src2[i] );

		n3.x = n1.x * h2[i] + n2.x * h1[i];
		n3.y = n1.y * h2[i] + n2.y * h1[i];
		n3.z = 1;

		dest[i] = normalize(n3);
	}
}

void normalize( unsigned char *data, int height, int width )
{
	int pos, i; 
	float3 normal;

	#pragma omp parallel for private(pos, normal)
	for( i = 0; i < height * width; i++ )
	{
		pos = i * 3;

		normal = make_float3( data[pos] / 127.5f - 1.0f, data[pos + 1] / 127.5f - 1.0f, data[pos + 2] / 127.5f - 1.0f );

		normal = normalize( normal );

		data[pos]     = (unsigned char)((normal.x + 1.0f) * 127.5f);
		data[pos + 1] = (unsigned char)((normal.y + 1.0f) * 127.5f);
		data[pos + 2] = (unsigned char)((normal.z + 1.0f) * 127.5f);		
	}
}

void normalize( float3 *data, int height, int width )
{
	#pragma omp parallel for
	for( int i = 0; i < height * width; i++ )
		data[i] = normalize( data[i] );		
}

void Normal2Height( float3 *normal, float *h, int height, int width )
{
	int height_odd, width_odd;
	int col2, row2;
	float low, high;
	int row, col;
	int i;
	float scale;

	float* h2 = new float[height * width];
	float* h3 = new float[height * width];
	float* h4 = new float[height * width];

	height_odd = height % 2;
	width_odd = width % 2;

	h[0] = 0;
	h2[0] = 0;
	h3[0] = 0;
	h4[0] = 0;

	for( i = 0; i < height * width; i++ )
	{
		scale = 1.0f / normal[i].z;

		normal[i].x *= scale;
		normal[i].y *= scale;
		normal[i].z *= scale;
	}

	if( height_odd && width_odd )
	{
		//Do x direction
		for( row = 0; row < height; row += 2 )
		{
			for( col = 0; col < width; col += 2 )
			{
				if( col != 0 )
				{
					h[row * width + col] = h[row * width + col - 2] - normal[row * width + col - 1].x; 
				}
				else if( row != 0 )
				{
					row2 = row - 2;

					h[row * width + col] = h[row2 * width + col] + normal[(row-2) * width + col].y;
				}
			}

			for( col = width - 2; col >= 0; col -= 2 )
			{
				h[row * width + col] = (h[row * width + col - 1] + h[row * width + col + 1]) / 2;
			}
		}

		for( row = height - 2; row >= 0; row -= 2 )
		{
			for( col = 0; col < width; col++ )
			{
				h[row * width + col] = (h[(row - 1) * width + col] + h[(row + 1) * width + col]) / 2;
			}
		}

		//Do x direction backward
		for( row = 2; row < height; row += 2 )
		{
			row2 = row - 2;

			h3[row * width] = h3[row2 * width] + normal[(row-1) * width].y;
		}

		for( row = 0; row < height; row += 2 )
		{
			for( col = width - 2; col > 0; col -= 2 )
			{
				col2 = col + 2;
				if( col2 == width )
					col2 = 0;
				h3[row * width + col] = h3[row * width + col2] + normal[row * width + col + 1].x; 
			}

			for( col = 0; col < width; col += 2 )
			{
				h3[row * width + col] = (h3[row * width + col - 1] + h3[row * width + col + 1]) / 2;
			}
		}

		for( row = height - 2; row >= 0; row -= 2 )
		{
			for( col = 0; col < width; col++ )
			{
				h3[row * width + col] = (h3[(row - 1) * width + col] + h3[(row + 1) * width + col]) / 2;
			}
		} 

		//Do y direction
		for( row = 0; row < height; row += 2 )
		{
			for( col = 0; col < width; col += 2 )
			{
				if( row != 0 )
				{
					h2[row * width + col] = h2[(row - 2) * width + col] + normal[(row-1) * width + col].y; 
				}
				else if( col != 0 )
				{
					h2[row * width + col] = h2[row * width + col - 2] - normal[row * width + col - 1].x; 
				}
			}

			for( col = width - 2; col >= 0; col -= 2 )
			{
				h2[row * width + col] = (h2[row * width + col - 1] + h2[row * width + col + 1]) / 2;
			}
		}

		for( row = height - 2; row >= 0; row -= 2 )
		{
			for( col = 0; col < width; col++ )
			{
				h2[row * width + col] = (h2[(row - 1) * width + col] + h2[(row + 1) * width + col]) / 2;
			}

		}

		//Do y direction Backward
		for( col = 2; col < width; col += 2 )
		{
			h4[col] = h4[col - 2] - normal[col - 1].x; 
		}

		for( row = height - 2; row >= 0; row -= 2 )
		{
			for( col = 0; col < width; col += 2 )
			{
				if( row != 0 )
				{
					row2 = (row + 2) % height;

					h4[row * width + col] = h4[row2 * width + col] - normal[(row + 1) * width + col].y; 
				}
			}

			for( col = width - 2; col >= 0; col -= 2 )
			{
				h4[row * width + col] = (h4[row * width + col - 1] + h4[row * width + col + 1]) / 2;
			}
		}

		for( row = 0; row < height; row += 2 )
		{
			for( col = 0; col < width; col++ )
			{
				h4[row * width + col] = (h4[(row - 1) * width + col] + h4[(row + 1) * width + col]) / 2;
			}

		}

	}
	else if( height_odd )
	{
		for( row = 0; row < height; row += 2 )
		{
			for( col = 0; col < width; col += 2 )
			{

			}

			for( col = 1; col < width; col += 2 )
			{

			}
		}

		for( row = height - 2; row > 0; row -= 2 )
		{
			for( col = 0; col < width; col++ )
			{

			}
		}
	}
	else if( width_odd )
	{
		for( row = 0; row < height; row += 2 )
		{
			for( col = 0; col < width; col += 2 )
			{

			}

			for( col = width - 2; col > 0; col -= 2 )
			{

			}
		}

		for( row = 1; row < height; row += 2 )
		{
			for( col = 0; col < width; col += 2 )
			{

			}

			for( col = width - 2; col > 0; col -= 2 )
			{

			}
		}
	}
	else
	{
		for( row = 0; row < height; row += 2 )
		{
			if( row == 0 )
			{
				for( col = 0; col < width; col += 2 )
				{

				}

				for( col = 1; col < width; col += 2 )
				{

				}
			}
			else
			{
				for( col = 0; col < width; col++ )
				{

				}
			}
		}

		for( row = 1; row < height; row += 2 )
		{
			if( row == 1 )
			{
				for( col = 0; col < width; col += 2 )
				{

				}

				for( col = 1; col < width; col += 2 )
				{
				
				}
			}
			else
			{
				for( col = 0; col < width; col++ )
				{

				}
			}
		}
	}

	low = high = h[0];

	for( i = 0; i < height * width; i++ )
	{
		if( h[i] < low )
			low = h[i];
		
		if( h[i] > high )
			high = h[i];
	}

	high = high - low;
	low = ABS(low);

	for( i = 0; i < height * width; i++ )
	{
		h[i] += low;
		h[i] /= high;
	}

	low = high = h2[0];

	for( i = 0; i < height * width; i++ )
	{
		if( h2[i] < low )
			low = h2[i];
		
		if( h2[i] > high )
			high = h2[i];
	}

	high = high - low;
	low = ABS(low);

	for( i = 0; i < height * width; i++ )
	{
		h2[i] += low;
		h2[i] /= high;
	}

	low = high = h3[0];

	for( i = 0; i < height * width; i++ )
	{
		if( h3[i] < low )
			low = h3[i];
		
		if( h3[i] > high )
			high = h3[i];
	}

	high = high - low;
	low = ABS(low);

	for( i = 0; i < height * width; i++ )
	{
		h3[i] += low;
		h3[i] /= high;
	}

	low = high = h4[0];

	for( i = 0; i < height * width; i++ )
	{
		if( h4[i] < low )
			low = h4[i];
		
		if( h4[i] > high )
			high = h4[i];
	}

	high = high - low;
	low = ABS(low);

	for( i = 0; i < height * width; i++ )
	{
		h4[i] += low;
		h4[i] /= high;
	}

	for( i = 0; i < height * width; i++ )
		h[i] = (h[i] + h2[i] + h3[i] + h4[i]) / 4;
	
	delete [] h2;
	delete [] h3;
	delete [] h4;
}

//Equations from http://en.wikipedia.org/wiki/Gaussian_blur
void GenerateExp(float range, float* expMatrix, int thread_id, int processors)
{
	int r = (int)ceil(range);
	float sigma_sq = range / 3.0f;
	sigma_sq *= sigma_sq * 2;

	int i;

	for( i = thread_id; i <= r; i += processors )
        expMatrix[i] = exp(-i*i/sigma_sq);
}

//Equations from http://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/MANDUCHI1/Bilateral_Filtering.html
void BilateralFilter(float3 *src, float3 *dest, int height, int width, float radius, float* cExp, float* sExp, int thread_id, int processors)
{
	int i;
	int size = height * width;
	float sum;
	float result;
	float temp;
	int row, col;
	int row2, col2;
	float val;
	int x, y;
	int r = (int)ceil(radius);
	
        for( i = thread_id; i < size; i += processors )
	{
		row = i / width;
		col = i % width;
		sum = 0;
		result = 0;

		for( x = -r; x <= r; x++ )
		{
            for( y = -r; y <= r; y++ )
			{
				row2 = row + y;
				col2 = col + x;

				if( row2 >= height )
					row2 %= height;
				else
				    while( row2 < 0 )
                        row2 += height;

				if( col2 >= width )
					col2 %= width;
				else
					while( col2 < 0 )
						col2 += width;

				val = src[row2 * width + col2].x * 255;

				if( val > 255.0f )
					val = 255.0f;

				temp = cExp[abs(x)] * cExp[abs(y)] * sExp[(int)val];
                sum += temp;
				result += src[row2 * width + col2].x * 255 * temp;
			}
		}

		result /= sum;
		dest[i].x = dest[i].y = dest[i].z = result / 255.0f;
	}
}

//Equations from http://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/MANDUCHI1/Bilateral_Filtering.html
void BilateralFilter(float *src, float *dest, int height, int width, float radius, float* cExp, float* sExp, int thread_id, int processors)
{
	int i;
	int size = height * width;
	float sum;
	float result;
	float temp;
	int row, col;
	int row2, col2;
	float val;
	int x, y;
	int r = (int)ceil(radius);

	for( i = thread_id; i < size; i += processors )
	{
		row = i / width;
		col = i % width;
		sum = 0;
		result = 0;

		for( x = -r; x <= r; x++ )
		{
            for( y = -r; y <= r; y++ )
			{
				row2 = row + y;
				col2 = col + x;

				if( row2 >= height )
					row2 %= height;
				else
				    while( row2 < 0 )
                        row2 += height;

				if( col2 >= width )
					col2 %= width;
				else
					while( col2 < 0 )
						col2 += width;

				val = abs(src[row2 * width + col2] - src[i]) * 255;

				if( val > 255 )
				{
					val = 255;
				}

				temp = cExp[abs(x)] * cExp[abs(y)] * sExp[(int)val];
                sum += temp;
				result += src[row2 * width + col2] * 255 * temp;
			}
		}

		result /= sum;
		dest[i] = result / 255.0f;
	}
}

void Grayscale(float3 *src, float3 *dest, int height, int width, int thread_id, int processors)
{
	int i;
	int size = height * width;

	for( i = thread_id; i < size; i += processors )
		dest[i].x = dest[i].y = dest[i].z = (.299f*src[i].x + .587f*src[i].y + .114f*src[i].z);
}

void Grayscale(float3 *src, float *dest, int height, int width, int thread_id, int processors)
{
	int i;
	int size = height * width;

	for( i = thread_id; i < size; i += processors)
		dest[i] = (.299f * src[i].x + .587f * src[i].y + .114f * src[i].z);
}

void Normal2SSBump(unsigned char *data, int height, int width, Modes mode, int thread_id, int processors)
{
	//float3 green_vector = make_float3((float)(-rsqrt(6.0f)), (float)(rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 blue_vector = make_float3((float)(-rsqrt(6.0f)), (float)(-rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 red_vector = make_float3((float)(sqrt(2.0f)/sqrt(3.0f)), 0.0f, (float)(rsqrt(3.0f)));

	float3 green_vector = make_float3( -0.40824829f,  0.70710678f, 0.57735027f );
	float3 blue_vector  = make_float3( -0.40824829f, -0.70710678f, 0.57735027f );
	float3 red_vector   = make_float3(  0.92210791f,  0.00000000f, 0.57735027f );

	float3 normal;
	int pos;
	float temp;
	float sum;
	float r, g, b;

	int i;

	switch( mode )
	{
	case N_DOT_L:
		for( i = thread_id; i < height * width; i += processors )
		{
			pos = i * 3;

			normal.x = data[pos] / 127.5f - 1.0f;
			normal.y = data[pos + 1] / 127.5f - 1.0f;
			normal.z = data[pos + 2] / 127.5f - 1.0f;

			r = saturate(dot( normal, red_vector ));
			g = saturate(dot( normal, green_vector ));
			b = saturate(dot( normal, blue_vector ));

			sum = r + g + b;
			data[pos] = (unsigned char)((r / sum) * 255);
			data[pos + 1] = (unsigned char)((g / sum) * 255);
			data[pos + 2] = (unsigned char)((b / sum) * 255);
		}
		break;
	case N_DOT_L2:
		for( i = thread_id; i < height * width; i += processors )
		{
			pos = i * 3;
			sum = 0;

			normal.x = data[pos] / 127.5f - 1.0f;
			normal.y = data[pos + 1] / 127.5f - 1.0f;
			normal.z = data[pos + 2] / 127.5f - 1.0f;

			temp = saturate(dot( normal, red_vector ));
			r = temp * temp;
			sum += r;

			temp = saturate(dot( normal, green_vector ));
			g = temp * temp;
			sum += g;

			temp = saturate(dot( normal, blue_vector ));
			b = temp * temp;
			sum += b;

			data[pos] = (unsigned char)((r / sum) * 255);
			data[pos + 1] = (unsigned char)((g / sum) * 255);
			data[pos + 2] = (unsigned char)((b / sum) * 255);
		}
		break;
/*	case N_DOT_L2:
		for( i = thread_id; i < height * width; i += processors )
		{
			pos = i * 3;

			normal.x = data[pos] / 127.5f - 1.0f;
			normal.y = data[pos + 1] / 127.5f - 1.0f;
			normal.z = data[pos + 2] / 127.5f - 1.0f;

			temp = saturate(dot( normal, red_vector ));
			data[pos] = (unsigned char)(temp * temp * 255);

			temp = saturate(dot( normal, green_vector ));
			data[pos + 1] = (unsigned char)( temp * temp * 255);

			temp = saturate(dot( normal, blue_vector ));
			data[pos + 2] = (unsigned char)( temp * temp * 255);
		}
		break; */
	case N_DOT_L4:
		for( i = thread_id; i < height * width; i += processors )
		{
			pos = i * 3;

			normal.x = data[pos] / 127.5f - 1.0f;
			normal.y = data[pos + 1] / 127.5f - 1.0f;
			normal.z = data[pos + 2] / 127.5f - 1.0f;
			
			temp =  1 - saturate(dot( normal, red_vector ));
			temp = temp * temp;
			temp *= temp;
			data[pos] = (unsigned char)((1 - temp) * 255);

			temp =  1 - saturate(dot( normal, green_vector ));
			temp = temp * temp;
			temp *= temp;
			data[pos + 1] = (unsigned char)((1 - temp) * 255);

			temp =  1 - saturate(dot( normal, blue_vector ));
			temp = temp * temp;
			temp *= temp;
			data[pos + 2] = (unsigned char)((1 - temp) * 255);
		}
		break;
	}
}

void Normal2SSBump(float3 *data, int height, int width, Modes mode, int thread_id, int processors)
{
	//float3 green_vector = make_float3((float)(-rsqrt(6.0f)), (float)(rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 blue_vector = make_float3((float)(-rsqrt(6.0f)), (float)(-rsqrt(2.0f)), (float)(rsqrt(3.0f)));
	//float3 red_vector = make_float3((float)(sqrt(2.0f)/sqrt(3.0f)), 0.0f, (float)(rsqrt(3.0f)));

	float3 green_vector = make_float3( -0.40824829f,  0.70710678f, 0.57735027f );
	float3 blue_vector  = make_float3( -0.40824829f, -0.70710678f, 0.57735027f );
	float3 red_vector   = make_float3(  0.92210791f,  0.00000000f, 0.57735027f );

	float red, green, blue;
	float temp;
	float3 normal;
	float sum;

	int i;

	switch( mode )
	{
	case N_DOT_L:
		for( i = thread_id; i < height * width; i += processors )
		{
			red = (saturate(dot( data[i], red_vector )));
			green = (saturate(dot( data[i], green_vector )));
			blue = (saturate(dot( data[i], blue_vector )));

			data[i].x = red;
			data[i].y = green;
			data[i].z = blue;

			sum = dot( data[i], make_float3(1.0f, 1.0f, 1.0f) );
			data[i].x /= sum;
			data[i].y /= sum;
			data[i].z /= sum;
		}
		break;
	case N_DOT_L2:
		for( i = thread_id; i < height * width; i += processors )
		{
			normal = data[i];

			temp = saturate(dot( normal, red_vector ));
			data[i].x = temp * temp;

			temp = saturate(dot( normal, green_vector ));
			data[i].y = temp * temp;

			temp = saturate(dot( normal, blue_vector ));
			data[i].z = temp * temp;

			sum = dot( data[i], make_float3(1.0f, 1.0f, 1.0f) );
			data[i].x /= sum;
			data[i].y /= sum;
			data[i].z /= sum;
		}
		break;

	case N_DOT_L4:
		for( i = thread_id; i < height * width; i += processors )
		{
			normal = data[i];
			
			temp =  1 - saturate(dot( normal, red_vector ));
			temp = temp * temp;
			temp *= temp;
			data[i].x = 1 - temp;

			temp =  1 - saturate(dot( normal, green_vector ));
			temp = temp * temp;
			temp *= temp;
			data[i].y = 1 - temp;

			temp =  1 - saturate(dot( normal, blue_vector ));
			temp = temp * temp;
			temp *= temp;
			data[i].z = 1 - temp;
		}
		break;
	}
}

//Algorithm from http://www.modwiki.net/wiki/Start_a_Specular_map_with_a_Normal_map
//Lighten_only blend from http://gimp-savvy.com/BOOK/index.html?node55.html
void Normal2Specular(unsigned char *data, int height, int width, int thread_id, int processors)
{
	int pos;
	unsigned char temp;

	int i;

	for( i = thread_id; i < height * width; i += processors )
	{
		pos = i * 3;

		temp = 128;

		temp = MAX( temp, data[pos] );
		temp = MAX( temp, (255 - data[pos]) );
		temp = MAX( temp, data[pos + 1] );
		temp = MAX( temp, (255 - data[pos + 1]) );

		data[pos] = data[pos + 1] = data[pos + 2] = temp;
	}
}

//Algorithm from http://www.modwiki.net/wiki/Start_a_Specular_map_with_a_Normal_map
//Lighten_only blend from http://gimp-savvy.com/BOOK/index.html?node55.html
void Normal2Specular(float3 *data, int height, int width, int thread_id, int processors)
{
	float temp;

	int i;

	for( i = thread_id; i < height * width; i += processors )
	{
		temp = 0.5f;

		data[i].x = (data[i].x + 1.0f) / 2;
		data[i].y = (data[i].y + 1.0f) / 2;

		temp = MAX( temp, data[i].x );
		temp = MAX( temp, (1.0f - data[i].x) );
		temp = MAX( temp, data[i].y );
		temp = MAX( temp, (1.0f - data[i].y) );

		data[i].x = data[i].y = data[i].z = temp;
	}
}

//Modified from code from ATI
void Normal2DuDv( unsigned char *data, int height, int width, int thread_id, int processors )
{
	int pos;

	for( int i = thread_id; i < height * width; i += processors )
	{
		pos = i * 3;

		data[pos] = (unsigned char)((int)data[i * 3] - 127);
		data[pos + 1] = (unsigned char)((int)data[i * 3 + 1] - 127);
		data[pos + 2] = 0;
	}
}

//Modified from code from ATI
void Normal2DuDv( float3 *data, int height, int width, int thread_id, int processors )
{
	for( int i = thread_id; i < height * width; i += processors )
	{
		data[i].x = (data[i].x + 1.0f) / 2;
		data[i].y = (data[i].y + 1.0f) / 2;

		data[i].x = data[i].x - 0.5f;
		data[i].y = data[i].y - 0.5f;
		data[i].z = 0;
	}
}

void Image2Height( unsigned char *data, int height, int width, int thread_id, int processors)
{

}

void Height2Normal( unsigned char *data, int height, int width, float scale, int thread_id, int processors)
{
	int i, col, row, pos;
	int left, right, up, down;

	float  *h = new float[height * width];
	float3  normal;

	for( i = 0; i < height * width; i++ )
		h[i] = ((int)data[i * 3] + (int)data[i * 3 + 1] + (int)data[i * 3 + 2]) / 765.0f * scale;

	for( i = thread_id; i < height * width; i += processors )
	{
		row = i / width;
		col = i % width;

		left = col - 1;
		right = col + 1;
		up = row - 1;
		down = row + 1;

		if( left < 0 )
			left = width - 1;
		else if( right >= width )
			right = 0;

		if( up < 0 )
			up = height - 1;
		else if( down >= height )
			down = 0;

		normal = GetNormal( h[down * width + col], h[up * width + col], h[row * width + right], h[row * width + left] );

		pos = i * 3;
		data[i]     = (unsigned char)((normal.x + 1.0f) * 127.5f);
		data[i + 1] = (unsigned char)((normal.y + 1.0f) * 127.5f);
		data[i + 2] = (unsigned char)((normal.z + 1.0f) * 127.5f);
	}

	delete [] h;
}

void Height2Normal( float3 *data, int height, int width, float scale, int thread_id, int processors)
{
	int i, col, row;
	int left, right, up, down;

	float  *h = new float[height * width];

	for( i = 0; i < height * width; i++ )
		h[i] = (data[i].x + data[i].y + data[i].z) / 3.0f * scale;

	for( i = thread_id; i < height * width; i += processors )
	{
		row = i / width;
		col = i % width;

		left = col - 1;
		right = col + 1;
		up = row - 1;
		down = row + 1;

		if( left < 0 )
			left = width - 1;
		else if( right >= width )
			right = 0;

		if( up < 0 )
			up = height - 1;
		else if( down >= height )
			down = 0;

		data[i] = GetNormal( h[down * width + col], h[up * width + col], h[row * width + right], h[row * width + left] );
	}

	delete [] h;
}

void Height2Normal( float *h, float3 *dest, int height, int width, int thread_id, int processors)
{
	int i, col, row;
	int left, right, up, down;

	for( i = thread_id; i < height * width; i += processors )
	{
		row = i / width;
		col = i % width;

		left = col - 1;
		right = col + 1;
		up = row - 1;
		down = row + 1;

		if( left < 0 )
			left = width - 1;
		else if( right >= width )
			right = 0;

		if( up < 0 )
			up = height - 1;
		else if( down >= height )
			down = 0;

		dest[i] = GetNormal( h[down * width + col], h[up * width + col], h[row * width + right], h[row * width + left] );
	}
}

/*
void NormalIntensity( float3 *normal, int height, int width, float intensity, int thread_id, int processors )
{
	int i;

	if( intensity >= 2.0f || intensity <= -2.0f )
		return;

	if( intensity == 0.0f )
	{
		for( i = 0; i < height * width; i++ )
		{
			normal[i].x = 0;
			normal[i].y = 0;
			normal[i].z = 1.0f;

			normal[i] = normalize( normal[i] );
		}
		return;
	}


	if( intensity > 1.0f || intensity < -1.0f )
	{
		if( intensity > 0 )
		{
			intensity -= 1.0f;
			intensity = 1.0f - intensity;
			for( i = 0; i < height * width; i++ )
			{
				normal[i].z *= intensity;

				normal[i] = normalize( normal[i] );
			}
		}
		else
		{
			intensity += 1.0f;
			intensity *= -1;
			intensity = 1.0f - intensity;
			for( i = 0; i < height * width; i++ )
			{
				normal[i].x *= -1;
				normal[i].y *= -1;
				normal[i].z *= intensity;

				normal[i] = normalize( normal[i] );
			}
		}
	}
	else
	{
		if( intensity > 0 )
		{
			intensity = 1.0f - intensity;
			intensity *= 8.0f;
			intensity = 1.0f + intensity;
			for( i = 0; i < height * width; i++ )
			{
				normal[i].z *= intensity;

				normal[i] = normalize( normal[i] );
			}
		}
		else
		{
			intensity *= -1;
			intensity = 1.0f - intensity;
			intensity *= 8.0f;
			intensity = 1.0f + intensity;
			for( i = 0; i < height * width; i++ )
			{
				normal[i].x *= -1;
				normal[i].y *= -1;
				normal[i].z *= intensity;

				normal[i] = normalize( normal[i] );
			}
		}
	}
} */

void NormalScale( float3 *normal, int height, int width, float intensity, int thread_id, int processors )
{
	int i;
	for( i = thread_id; i < height * width; i += processors )
	{
		normal[i].x *= intensity;
		normal[i].y *= intensity;

		normal[i] = normalize(normal[i]);
	}
}

void NormalEdges( float3 *normal, float *h, int height, int width, float strength, float intensity, int thread_id, int processors )
{
	float *temp = new float[height * width];
	float temp_f;
//	int row, col;
//	int right, left, up, down;
	int i;

	if( intensity < 0.0f )
		intensity = 0.0f;
	else if( intensity > 1.0f )
		intensity = 1.0f;

/*	for( i = thread_id; i < height * width; i += processors )
	{
		row = i / width;
		col = i % width;

		right = col + 1;
		left = col - 1;
		up = row - 1;
		down = row + 1;

		if( left < 0 )
			left = width - 1;
		else if( right >= width )
			right = 0;

		if( up < 0 )
			up = height - 1;
		else if( down >= height )
			down = 0;

		temp[row * width + col] = 1.0f - ComputeSobel( h[up * width + left], h[up * width + col],
			                                           h[up * width + right], h[row * width + left],
										    		   h[row * width + col], h[row * width + right],
											           h[down * width + left], h[down * width + col],
												       h[down * width + right], strength );
	} */

	for( i = thread_id; i < height * width; i += processors )
	{
		temp_f = 0.0f;

		temp_f = MAX( temp_f, ABS(normal[i].x) );
		temp_f = MAX( temp_f, ABS(normal[i].y) );

		temp[i] = 1.0f - MIN(temp_f * strength, 1.0f);
	}

	for( i = thread_id; i < height * width; i += processors )
	{
		normal[i].z *= ( MAX( 0.01f, MIN( temp[i] + (1.0f - intensity), 1.0f )) );

		normal[i] = normalize( normal[i] );
	}

	delete [] temp;
}

void Height2DirectionalAO( unsigned char *data, float* h, int height, int width,
						   ray* red, ray* blue, ray* green, int rays, float scale,
						   float radius, bool tile, bool h_tile, bool v_tile,
						   int thread_id, int processors, int* complete )
{
	int row, col;
	long pos, i, px;
	float max_height_val = 0.0f;
	float shadow;
	int max_dist = (int)(radius * width + 0.5f);
	int temp;

	temp = 0;

	if( complete == NULL )
		complete = &temp;

	//Find highest point
	for( i = 0; i < height * width; i++ )
	{
		if( h[i] > max_height_val )
			max_height_val = h[i];
		else if( max_height_val == 1.0f )
			break;
	}

	//Start processing image
	for( pos = thread_id; pos < height * width; pos += processors)
	{
		col = pos % width;
	    row = pos / width;
		px = pos * 3;

		//Calculate Red Color
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, red, max_dist, tile, h_tile, v_tile);
		shadow = saturate(shadow);
		data[px] = (unsigned char)(shadow * 255.0f); 

		//Calculate Green value
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, green, max_dist, tile, h_tile, v_tile);		
		shadow = saturate(shadow);
		data[px + 1] = (unsigned char)(shadow * 255.0f);

		//Calculate Blue Color
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, blue, max_dist, tile, h_tile, v_tile);
		shadow = saturate(shadow);
		data[px + 2] = (unsigned char)(shadow * 255.0f);
	
		if( thread_id == 0 )
		{
			//Update Status
			*complete = (int)((float)pos / (height * width) * 1000);
		}
	}
}

void ChangeDepth(float * h, int height, int width, float amount, float scale, int thread_id, int processors)
{
	int i;
	float mid = 0.5f * scale;

	for(i = thread_id; i < width * height; i += processors)
		h[i] = h[i] + ((h[i] - mid) * amount);
}

void Contrast(float * data, int height, int width, float contrast, int thread_id, int processors)
{
	int i;

	for(i = thread_id; i < width * height; i += processors)
		data[i] = saturate(data[i] + ((data[i] - 0.5f) * contrast));
}

void Height2DirectionalAO( float3 *data, float* h, int height, int width,
						   ray* red, ray* blue, ray* green, int rays, float scale,
						   float radius, bool tile, bool h_tile, bool v_tile,
						   int thread_id, int processors, int* complete )
{
	int row, col;
	long pos, i;
	float max_height_val = 0.0f;
	float shadow;
	int max_dist = (int)(radius * width + 0.5f);
	int temp;

	temp = 0;

	if( complete == NULL )
		complete = &temp;

	//Find highest point
	for( i = 0; i < height * width; i++ )
	{
		if( h[i] > max_height_val )
			max_height_val = h[i];
		else if( max_height_val == 1.0f )
			break;
	}

	//Start processing image
	for( pos = thread_id; pos < height * width; pos += processors)
	{
		col = pos % width;
	    row = pos / width;

		//Calculate Red Color
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, red, max_dist, tile, h_tile, v_tile);
		data[pos].x = saturate(shadow);

		//Calculate Green value
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, green, max_dist, tile, h_tile, v_tile);		
		data[pos].y = saturate(shadow);

		//Calculate Blue Color
		shadow = trace_rays(h, height, width, row, col, rays, max_height_val, 
			                scale, radius, blue, max_dist, tile, h_tile, v_tile);
		data[pos].z = saturate(shadow);
	
		if( thread_id == 0 )
		{
			//Update Status
			*complete = (int)((float)pos / (height * width) * 1000);
		}
	}
}

void BlendNormal( float percent, float3 *src1, float3 *src2, float3 *dest, int height, int width, int thread_id, int processors)
{
	int i;

	float3 n1, n2, n3;

	if( percent >= 100.0f )
		percent = 1.0f;
	else if( percent < 0.0f )
		percent = 0.0f;
	else
		percent /= 100.0f;

	for( i = thread_id; i < height * width; i += processors )
	{
		n1 = ret_deriv( src1[i] );
		n2 = ret_deriv( src2[i] );

		n3.x = n2.x * percent + n1.x * (1 - percent);
		n3.y = n2.y * percent + n1.y * (1 - percent);
		n3.z = n2.z * percent + n1.z * (1 - percent);

		dest[i] = normalize(n3);
	}
}

//Equations From
//Grokking the GIMP
//By Carey Bunks
//http://gimp-savvy.com/BOOK/index.html?node55.html
void Blend( BlendType type, float percent, unsigned char *src, unsigned char *src2, unsigned char *dest, int height, int width, int thread_id, int processors)
{
	int i, j;
	unsigned char temp_c;
	float temp1, temp2, screen, result;
	float r, g, b;
	float hue, saturation, value, lightness;
	int h;
	float min, max;
	float f, p, q, t, h_f;
	float pixel[3] = {0.0f};

	if( percent >= 100.0f )
		percent = 1.0f;
	else if( percent < 0.0f )
		percent = 0.0f;
	else
		percent /= 100.0f;

	switch( type )
	{
	case DEFAULT:
		//Modified from code
		//Copyright (c) Alex Cornejo
		//http://people.csail.mit.edu/acornejo/html/blender.htm
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + src[i] * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + src[i + 1] * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + src[i + 2] * percent);
		}
		break;

	case OVERLAY:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			temp1 = src2[i] / 255.0f;
			temp2 = src[i] / 255.0f;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i] = (unsigned char)((temp1 * (1.0f - percent) + result * percent) * 255);

			temp1 = src2[i + 1] / 255.0f;
			temp2 = src[i + 1] / 255.0f;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i + 1] = (unsigned char)((temp1 * (1.0f - percent) + result * percent) * 255);

			temp1 = src2[i + 2] / 255.0f;
			temp2 = src[i + 2] / 255.0f;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i + 2] = (unsigned char)((temp1 * (1.0f - percent) + result * percent) * 255);
		}
		break;

	case SCREEN:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			//temp_c = ~(unsigned char)(((int)(~src[i]) * ~src2[i]) >> 8);
			temp_c = 255 - (((255 - (int)src[i]) * (255 - (int)src2[i])) >> 8);
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			//temp_c = ~(unsigned char)(((int)(~src[i + 1]) * ~src2[i + 1]) >> 8);
			temp_c = 255 - (((255 - (int)src[i + 1]) * (255 - (int)src2[i + 1])) >> 8);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			//temp_c = ~(unsigned char)(((int)(~src[i + 2]) * ~src2[i + 2]) >> 8);
			temp_c = 255 - (((255 - (int)src[i + 2]) * (255 - (int)src2[i + 2])) >> 8);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case LIGHTEN:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + MAX( src2[i], src[i] ) * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + MAX( src2[i + 1], src[i + 1] ) * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + MAX( src2[i + 2], src[i + 2] ) * percent);
		}
		break;

	case DARKEN:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + MIN( src2[i], src[i] ) * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + MIN( src2[i + 1], src[i + 1] ) * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + MIN( src2[i + 2], src[i + 2] ) * percent);
		}
		break;

	case MULTIPLY:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			temp_c = (unsigned char)(((int)src2[i] * src[i]) >> 8);
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)(((int)src2[i + 1] * src[i + 1]) >> 8);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)(((int)src2[i + 2] * src[i + 2]) >> 8);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case DIVIDE:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			temp_c = (unsigned char)( MIN(255, ((int)src2[i] << 8) / ((int)src[i] + 1) ) );
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MIN(255, ((int)src2[i + 1] << 8) / ((int)src[i + 1] + 1) ) );
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MIN(255, ((int)src2[i + 2] << 8) / ((int)src[i + 2] + 1) ) );
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case ADDITION:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			temp_c = (unsigned char)( MIN( (int)src[i] + (int)src2[i], 255 ) );
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MIN( (int)src[i + 1] + (int)src2[i + 1], 255 ) );
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MIN( (int)src[i + 2] + (int)src2[i + 2], 255 ) );
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case SUBTRACTION:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			temp_c = (unsigned char)( MAX( (int)src2[i] - (int)src[i], 0 ) );
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MAX( (int)src2[i + 1] - (int)src[i + 1], 0 ) );
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( MAX( (int)src2[i + 2] - (int)src[i + 2], 0 ) );
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case DIFF:
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			temp_c = (unsigned char)( ABS( (int)src2[i] - (int)src[i] ) );
			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( ABS( (int)src2[i + 1] - (int)src[i + 1] ) );
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + temp_c * percent);

			temp_c = (unsigned char)( ABS( (int)src2[i + 2] - (int)src[i + 2] ) );
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + temp_c * percent);
		}
		break;

	case HUE:
		//Hue, Saturation, Value Equations from Wikipedia
		//http://en.wikipedia.org/wiki/HSL_and_HSV#Formal_specifications
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			//Convert RGB to HSV
			r = src[i] / 255.0f;
			g = src[i + 1] / 255.0f;
			b = src[i + 2] / 255.0f;

			max = MAX3(r, g, b);
			min = MAX3(r, g, b);

			if( max == min )
				hue = 0;
			else if( max == r )
				hue = (float)((int)(60 * (g - b) / (max - min) + 360) % 360);
			else if( max == g)
				hue = 60 * (b - r) / (max - min) + 120;
			else //max == b
				hue = 60 * (r - g) / (max - min) + 240;

			r = src2[i] / 255.0f;
			g = src2[i + 1] / 255.0f;
			b = src2[i + 2] / 255.0f;

			if( MAX3(r, g, b) == 0 )
				saturation = 0.0f;
			else
				saturation = 1.0f - (MIN3(r, g, b)/MAX3(r, g, b));
			value = MAX3(r, g, b);

			//Convert HSV to RGB
			h = (int)(hue / 60) % 6;
			f = hue/60 - (int)hue/60;
			p = value * (1 - saturation);
			q = value * (1 - (f * saturation));
			t = value * (1 - ((1 - f) * saturation));

			switch( h )
			{
			case 0:
				//v,t,p
				r = value * 255;
				g = t * 255;
				b = p * 255;
				break;

			case 1:
				//q,v,p
				r = q * 255;
				g = value * 255;
				b = p * 255;
				break;

			case 2:
				//p,v,t
				r = p * 255;
				g = value * 255;
				b = t * 255;
				break;

			case 3:
				//p,q,v
				r = p * 255;
				g = q * 255;
				b = value * 255;
				break;

			case 4:
				//t,p,v
				r = t * 255;
				g = p * 255;
				b = value * 255;
				break;

			case 5:
				//v,p,q
				r = value * 255;
				g = p * 255;
				b = q * 255;
				break;
			}

			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + r * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + g * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + b * percent);
		}
		break;

	case SATURATION:
		//Hue, Saturation, Value Equations from Wikipedia
		//http://en.wikipedia.org/wiki/HSL_and_HSV#Formal_specifications
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			//Convert RGB to HSV
			r = src2[i] / 255.0f;
			g = src2[i + 1] / 255.0f;
			b = src2[i + 2] / 255.0f;

			max = MAX3(r, g, b);
			min = MAX3(r, g, b);

			if( max == min )
				hue = 0;
			else if( max == r )
				hue = (float)((int)(60 * (g - b) / (max - min) + 360) % 360);
			else if( max == g)
				hue = 60 * (b - r) / (max - min) + 120;
			else //max == b
				hue = 60 * (r - g) / (max - min) + 240;

			value = MAX3(r, g, b);

			r = src[i] / 255.0f;
			g = src[i + 1] / 255.0f;
			b = src[i + 2] / 255.0f;

			saturation = 1.0f - (MIN3(r, g, b)/MAX3(r, g, b));

			//Convert HSV to RGB
			h = (int)(hue / 60) % 6;
			f = hue/60 - (int)hue/60;
			p = value * (1 - saturation);
			q = value * (1 - f * saturation);
			t = value * (1 - (1 - f) * saturation);

			switch( h )
			{
			case 0:
				//v,t,p
				r = value * 255;
				g = t * 255;
				b = p * 255;
				break;

			case 1:
				//q,v,p
				r = q * 255;
				g = value * 255;
				b = p * 255;
				break;

			case 2:
				//p,v,t
				r = p * 255;
				g = value * 255;
				b = t * 255;
				break;

			case 3:
				//p,q,v
				r = p * 255;
				g = q * 255;
				b = value * 255;
				break;

			case 4:
				//t,p,v
				r = t * 255;
				g = p * 255;
				b = value * 255;
				break;

			case 5:
				//v,p,q
				r = value * 255;
				g = p * 255;
				b = q * 255;
				break;
			}

			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + r * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + g * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + b * percent);
		}
		break;

	case VALUE:
		//Hue, Saturation, Value Equations from Wikipedia
		//http://en.wikipedia.org/wiki/HSL_and_HSV#Formal_specifications
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			//Convert RGB to HSV
			r = src2[i] / 255.0f;
			g = src2[i + 1] / 255.0f;
			b = src2[i + 2] / 255.0f;

			max = MAX3(r, g, b);
			min = MAX3(r, g, b);

			if( max == min )
				hue = 0;
			else if( max == r )
				hue = (float)((int)(60 * (g - b) / (max - min) + 360) % 360);
			else if( max == g)
				hue = 60 * (b - r) / (max - min) + 120;
			else //max == b
				hue = 60 * (r - g) / (max - min) + 240;

			saturation = 1.0f - (MIN3(r, g, b)/MAX3(r, g, b));

			r = src[i] / 255.0f;
			g = src[i + 1] / 255.0f;
			b = src[i + 2] / 255.0f;

			value = MAX3(r, g, b);

			//Convert HSV to RGB
			h = (int)(hue / 60) % 6;
			f = hue/60 - (int)hue/60;
			p = value * (1 - saturation);
			q = value * (1 - f * saturation);
			t = value * (1 - (1 - f) * saturation);

			switch( h )
			{
			case 0:
				//v,t,p
				r = value * 255;
				g = t * 255;
				b = p * 255;
				break;

			case 1:
				//q,v,p
				r = q * 255;
				g = value * 255;
				b = p * 255;
				break;

			case 2:
				//p,v,t
				r = p * 255;
				g = value * 255;
				b = t * 255;
				break;

			case 3:
				//p,q,v
				r = p * 255;
				g = q * 255;
				b = value * 255;
				break;

			case 4:
				//t,p,v
				r = t * 255;
				g = p * 255;
				b = value * 255;
				break;

			case 5:
				//v,p,q
				r = value * 255;
				g = p * 255;
				b = q * 255;
				break;
			}

			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + r * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + g * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + b * percent);
		}
		break;

	case COLOR:
		//Hue, Saturation, Value Equations from Wikipedia
		//http://en.wikipedia.org/wiki/HSL_and_HSV#Formal_specifications
		for( i = thread_id; i < height * width * 3; i += 3 * processors )	
		{
			//Convert RGB to HSL
			r = src[i] / 255.0f;
			g = src[i + 1] / 255.0f;
			b = src[i + 2] / 255.0f;

			max = MAX3(r, g, b);
			min = MAX3(r, g, b);

			if( max == min )
				hue = 0;
			else if( max == r )
				hue = (float)((int)(60 * (g - b) / (max - min) + 360) % 360);
			else if( max == g)
				hue = 60 * (b - r) / (max - min) + 120;
			else //max == b
				hue = 60 * (r - g) / (max - min) + 240;

			lightness = 0.5f * (MIN3(r, g, b) + MAX3(r, g, b));

			if( max == min )
				saturation = 0.0f;
			else if( lightness <= 0.5f )
				saturation = (max - min) / (2 * lightness);
			else //lightness > 0.5f
				saturation = (max - min) / (2 - 2 * lightness);

			r = src2[i] / 255.0f;
			g = src2[i + 1] / 255.0f;
			b = src2[i + 2] / 255.0f;

			lightness = 0.5f * (MIN3(r, g, b) + MAX3(r, g, b));

			//Convert HSL to RGB
			if( saturation == 0.0f )
			{
				pixel[RED] = pixel[GREEN] = pixel[BLUE] = lightness;
			}
			else
			{
				if( lightness < 0.5f )
					q = lightness * (1 + saturation);
				else
					q = lightness + saturation - lightness * saturation;

				p = 2 * lightness - q ;
				h_f = height / 360.0f;

				pixel[RED] = h_f + 1.0f/3.0f;
				if( pixel[RED] < 0 )
					pixel[RED] += 1.0f;
				else if( pixel[RED] > 1.0f )
					pixel[RED] -= 1.0f;

				pixel[GREEN] = h_f;
				if( pixel[GREEN] < 0 )
					pixel[GREEN] += 1.0f;
				else if( pixel[GREEN] > 1.0f )
					pixel[GREEN] -= 1.0f;

				pixel[BLUE] = h_f - 1.0f/3.0f;
				if( pixel[BLUE] < 0 )
					pixel[BLUE] += 1.0f;
				else if( pixel[BLUE] > 1.0f )
					pixel[BLUE] -= 1.0f;

				for( j = 0; j < 3; j++ )
				{
					if( pixel[j] < 1.0f/6.0f )
						pixel[j] = p + ((q - p) * 6 * pixel[j]);
					else if( pixel[j] < 0.5f )
						pixel[j] = q;
					else if( pixel [j] < 2.0f/3.0f )
						pixel[j] = p + ((q - p) * 6 * (2.0f/3.0f - pixel[j]));
					else
						pixel[j] = p;
				}
			}

			dest[i] = (unsigned char)(src2[i] * (1.0f - percent) + pixel[RED] * percent);
			dest[i + 1] = (unsigned char)(src2[i + 1] * (1.0f - percent) + pixel[GREEN] * percent);
			dest[i + 2] = (unsigned char)(src2[i + 2] * (1.0f - percent) + pixel[BLUE] * percent);
		}
		break;
	}
}

void Blend( BlendType type, float percent, float3 *src2, float3 *src, float3 *dest, int height, int width, int thread_id, int processors )
{
	int i;
	float temp_c;
	float temp1, temp2, screen, result;

	if( percent >= 100.0f )
		percent = 1.0f;
	else if( percent < 0.0f )
		percent = 0.0f;
	else
		percent /= 100.0f;

	switch( type )
	{
	case DEFAULT:
		//Modified from code
		//Copyright (c) Alex Cornejo
		//http://people.csail.mit.edu/acornejo/html/blender.htm
		for( i = thread_id; i < height * width; i += processors )	
		{
			dest[i].x = src2[i].x * (1.0f - percent) + src[i].x * percent;
			dest[i].y = src2[i].y * (1.0f - percent) + src[i].y * percent;
			dest[i].z = src2[i].z * (1.0f - percent) + src[i].z * percent;
		}
		break;

	case OVERLAY:
		for( i = thread_id; i < height * width; i += processors )	
		{
			temp1 = src2[i].x;
			temp2 = src[i].x;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i].x = temp1 * (1.0f - percent) + result * percent;

			temp1 = src2[i].y;
			temp2 = src[i].y;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i].y = temp1 * (1.0f - percent) + result * percent;

			temp1 = src2[i].z;
			temp2 = src[i].z;
			screen = 1.0f - (1.0f - temp2) * (1.0f - temp1);
			result = temp1 * screen + (1.0f - temp1) * temp1 * temp2;
			dest[i].z = temp1 * (1.0f - percent) + result * percent;
		}
		break;

	case SCREEN:
		for( i = thread_id; i < height * width; i += processors )	
		{
			temp_c = 1.0f - (1.0f - src[i].x) * (1.0f - src2[i].x);
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = 1.0f - (1.0f - src[i].y) * (1.0f - src2[i].y);
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = 1.0f - (1.0f - src[i].z) * (1.0f - src2[i].z);
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case LIGHTEN:
		for( i = thread_id; i < height * width; i += processors )	
		{
			dest[i].x = src2[i].x * (1.0f - percent) + MAX( src2[i].x, src[i].x ) * percent;
			dest[i].y = src2[i].y * (1.0f - percent) + MAX( src2[i].y, src[i].y ) * percent;
			dest[i].z = src2[i].z * (1.0f - percent) + MAX( src2[i].z, src[i].z ) * percent;
		}
		break;

	case DARKEN:
		for( i = thread_id; i < height * width; i += processors )	
		{
			dest[i].x = src2[i].x * (1.0f - percent) + MIN( src2[i].x, src[i].x ) * percent;
			dest[i].y = src2[i].y * (1.0f - percent) + MIN( src2[i].y, src[i].y ) * percent;
			dest[i].z = src2[i].z * (1.0f - percent) + MIN( src2[i].z, src[i].z ) * percent;
		}
		break;

	case MULTIPLY:
		for( i = thread_id; i < height * width; i += processors )	
		{
			temp_c = src2[i].x * src[i].x;
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = src2[i].y * src[i].y;
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = src2[i].z * src[i].z;
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case DIVIDE:
		for( i = thread_id; i < height * width; i += processors )	
		{
			temp_c = MIN(1.0f, src2[i].x / MAX(0.0039215f, src[i].x + 1) );
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = MIN(1.0f, src2[i].x / MAX(0.0039215f, src[i].y + 1) );
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = MIN(1.0f, src2[i].x / MAX(0.0039215f, src[i].z + 1) );
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case ADDITION:
		for( i = thread_id; i < height * width; i += processors )	
		{
			temp_c = MIN( src[i].x + src2[i].x, 1.0f );
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = MIN( src[i].y + src2[i].y, 1.0f ) ;
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = MIN( src[i].z + src2[i].z, 1.0f ) ;
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case SUBTRACTION:
		for( i = thread_id; i < height * width; i += processors )	
		{
			temp_c = MAX( src2[i].x - src[i].x, 0 );
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = MAX( src2[i].y - src[i].y, 0 );
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = MAX( src2[i].z - src[i].z, 0 );
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

	case DIFF:
		for( i = thread_id; i < height * width; i += processors )	
		{
			temp_c = ABS( src2[i].x - src[i].x );
			dest[i].x = src2[i].x * (1.0f - percent) + temp_c * percent;

			temp_c = ABS( src2[i].y - src[i].y );
			dest[i].y = src2[i].y * (1.0f - percent) + temp_c * percent;

			temp_c = ABS( src2[i].z - src[i].z );
			dest[i].z = src2[i].z * (1.0f - percent) + temp_c * percent;
		}
		break;

        case SATURATION:
        case VALUE:
        case COLOR:
        case HUE:
                break;
	}
}

void NormalOverlay( float3* src1, float3* src2, float3* dest, float* h1, float* h2, int height, int width, int thread_id, int processors )
{
	int i;

	float3 n1, n2, n3;

	for( i = thread_id; i < height * width; i += processors )
	{
		n1 = ret_deriv( src1[i] );
		n2 = ret_deriv( src2[i] );

		n3.x = n2.x - 2*h2[i]*n2.x + n1.x*h2[i]*h2[i]*h2[i] + 3*h2[i]*h2[i]*n2.x*h1[i] + n1.x*h2[i] + n2.x*h1[i] - 2*n1.x*h2[i]*h2[i] + 4*h2[i]*n2.x*h1[i];
		n3.y = n2.y - 2*h2[i]*n2.y + n1.y*h2[i]*h2[i]*h2[i] + 3*h2[i]*h2[i]*n2.y*h1[i] + n1.y*h2[i] + n2.y*h1[i] - 2*n1.y*h2[i]*h2[i] + 4*h2[i]*n2.y*h1[i];
		n3.z = 1;

		dest[i] = normalize(n3);
	}
}

void NormalModulation( float3* src1, float3* src2, float3* dest, float* h1, float* h2, int height, int width, int thread_id, int processors )
{
	int i;

	float3 n1, n2, n3;

	for( i = thread_id; i < height * width; i += processors )
	{
		n1 = ret_deriv( src1[i] );
		n2 = ret_deriv( src2[i] );

		n3.x = n1.x * h2[i] + n2.x * h1[i];
		n3.y = n1.y * h2[i] + n2.y * h1[i];
		n3.z = 1;

		dest[i] = normalize(n3);
	}
}

void normalize( unsigned char *data, int height, int width, int thread_id, int processors )
{
	int pos, i; 
	float3 normal;

	for( i = thread_id; i < height * width; i += processors )
	{
		pos = i * 3;

		normal = make_float3( data[pos] / 127.5f - 1.0f, data[pos + 1] / 127.5f - 1.0f, data[pos + 2] / 127.5f - 1.0f );

		normal = normalize( normal );

		data[pos]     = (unsigned char)((normal.x + 1.0f) * 127.5f);
		data[pos + 1] = (unsigned char)((normal.y + 1.0f) * 127.5f);
		data[pos + 2] = (unsigned char)((normal.z + 1.0f) * 127.5f);		
	}
}

void normalize( float3 *data, int height, int width, int thread_id, int processors )
{
	for( int i = thread_id; i < height * width; i += processors )
		data[i] = normalize( data[i] );		
}

float3 make_float3(float x, float y, float z)
{
    float3 tmp;

    tmp.x = x;
    tmp.y = y;
    tmp.z = z;

    return tmp;
}

//Modified from code Copyright 2005 Huxtable.com
//http://www.jhlabs.com/ip/blurring.html
int MakeKernel(float* & matrix, float radius)
{
        int r = (int)ceil(radius);
        int rows = r * 2 + 1;
        matrix = new float[rows];
        float sigma = radius / 3;
        float sigma22 = 2 * sigma * sigma;
        float sigmaPi2 = (float)(2 * PI * sigma);
        float sqrtSigmaPi2 = (float)sqrt(sigmaPi2);
        float radius2 = radius * radius;
        float total = 0;
        int index = 0, row, i;
        float distance;
        for(row = -r; row <= r; row++)
        {
                distance = (float)(row * row);
                if (distance > radius2)
                        matrix[index] = 0;
                else
                        matrix[index] = (float)exp(-(distance)/sigma22) / sqrtSigmaPi2;
                total += matrix[index];
                index++;
        }
        for (i = 0; i < rows; i++)
                matrix[i] /= total;

        return rows;
}

//Modified from code Copyright 2005 Huxtable.com
//http://www.jhlabs.com/ip/blurring.html
void Blur( float* inPixels, float* outPixels, int width, int height, float radius )
{
                float *matrix = NULL;
                int cols = MakeKernel(matrix, radius);
                float *temp = new float[ height * width];

                ConvolveAndTranspose(matrix, inPixels, temp, width, height, cols, false);
                ConvolveAndTranspose(matrix, temp, outPixels, height, width, cols, false);

                delete [] matrix;
                delete [] temp;
}

//Modified from code Copyright 2005 Huxtable.com
//http://www.jhlabs.com/ip/blurring.html
void ConvolveAndTranspose(float* matrix, float *inPixels, float *outPixels, int width, int height, int cols, int edgeAction)
{
        int cols2 = cols/2;
        int index, ioffset;
        int y;

        #pragma omp parallel for private(index, ioffset)
        for(y = 0; y < height; y++)
        {
                index = y;
                ioffset = y * width;
                #pragma omp parallel for
                for(int x = 0; x < width; x++)
                {
                        float r, f;
                        int ix, col;
                        int moffset;

                        r = 0;
                        moffset = cols2;
                        for(col = -cols2; col <= cols2; col++)
                        {
                                f = matrix[moffset+col];

                                if(f != 0)
                                {
                                        ix = x+col;
                                        if( ix < 0 )
                                        {
                                                if( edgeAction )
                                                        ix = 0;
                                                else
                                                        ix = (x+width) % width;
                                        }
                                        else if( ix >= width)
                                        {
                                                if( edgeAction )
                                                        ix = width-1;
                                                else
                                                        ix = (x+width) % width;
                                        }
                                        r += f * inPixels[ioffset+ix];
                                }
                        }
                        outPixels[index] = r;
            index += height;
                }
        }
}
