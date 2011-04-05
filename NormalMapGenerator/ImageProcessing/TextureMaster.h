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

#ifndef __TEXTUREMASTER__
#define __TEXTUREMASTER__

#include "My_Math.h"
#include "HLSL_Func.h"
#include "Misc_Func.h"
#include <omp.h>

typedef unsigned int uint;
typedef unsigned char uchar;

enum Modes{ N_DOT_L, N_DOT_L2, N_DOT_L4 };
enum BlendType{ DEFAULT, OVERLAY, SCREEN, LIGHTEN, DARKEN, MULTIPLY, DIVIDE, ADDITION, SUBTRACTION, DIFF, HUE, SATURATION, VALUE, COLOR };

void  Normal2SSBump( unsigned char *data, int height, int width, Modes mode, int thread_id, int processors );
void  Normal2SSBump( float3 *data, int height, int width, Modes mode, int thread_id, int processors );
void  Normal2Specular(unsigned char *data, int height, int width, int thread_id, int processors );
void  Normal2Specular(float3 *data, int height, int width, int thread_id, int processors );
void  Normal2DuDv( unsigned char *data, int height, int width, int thread_id, int processors );
void  Normal2DuDv( float3 *data, int height, int width, int thread_id, int processors );
void  Image2Height( unsigned char *data, int height, int width, \
                    int thread_id, int processors );
void  Height2Normal( float *h, float3 *dest, int height, int width, int thread_id, int processors );
void  Height2Normal( unsigned char *data, int height, int width, \
                     float scale, int thread_id, int processors );
void  Height2Normal( float3 *data, int height, int width,   \
                     float scale, int thread_id, int processors );
void  GenerateRays( int height, int width, ray* &red, ray* &blue, ray* &green,            \
                    int rays = 300, float theta_limit = 120.0f, float alpha_limit = 120.0f );
void  Height2DirectionalAO( unsigned char *data, float* h, int height, int width, ray* red, \
                            ray* blue, ray* green, int rays = 300, float scale = 0.1f,      \
                            float radius = 0.1f, bool tile = true, bool h_tile = true,      \
                            bool v_tile = true, int thread_id = 0, int processors = 1,      \
                            int *complete = NULL );
void  Height2DirectionalAO( float3 *data, float* h, int height, int width, ray* red,   \
                            ray* blue, ray* green, int rays = 300, float scale = 0.1f, \
                            float radius = 0.1f, bool tile = true, bool h_tile = true, \
                            bool v_tile = true, int thread_id = 0, int processors = 1, \
                            int *complete = NULL );
void  Blend( BlendType type , float percent, unsigned char *src,    \
             unsigned char *src2, unsigned char *dest, int height, \
			          int width, int thread_id = 0, int processors = 1);
void  Blend( BlendType type , float percent, float3 *src,        \
             float3 *src2, float3 *dest, int height, int width, \
             int thread_id, int processors );
void  normalize( unsigned char *data, int height, int width, \
                 int thread_id, int processors );
void  normalize( float3 *data, int height, int width,  \
                 int thread_id, int processors );

void  ChangeDepth(float * h, int height, int width, float amount, float scale, int thread_id, int processors );
void  Contrast(float * data, int height, int width, float contrast, int thread_id, int processors );
void  NormalScale( float3 *normal, int height, int width, float intensity, int thread_id, int processors );
void  BlendNormal( float percent, float3 *src, float3 *src2, float3 *dest, int height, int width, int thread_id, int processors );
void  NormalModulation( float3* n1, float3* n2, float3* dest, float* h1, float* h2, int height, int width, int thread_id, int processors );
void  NormalOverlay( float3* src1, float3* src2, float3* dest, float* h1, float* h2, int height, int width, int thread_id, int processors );
void  NormalEdges( float3 *normal, float *h, int height, int width, float strength, float intensity, int thread_id, int processors );

void  Normal2Height( float3 *normal, float *h, int height, int width );

void  Grayscale(float3 *src, float3 *dest, int height, int width, int thread_id, int processors );
void  Grayscale(float3 *src, float *dest, int height, int width, int thread_id, int processors );

void  GenerateExp(float range, float* expMatrix, int thread_id, int processors );
void  BilateralFilter(float *src, float *dest, int height, int width, float radius, float* cExp, float* sExp, int thread_id, int processors );
void  BilateralFilter(float3 *src, float3 *dest, int height, int width, float radius, float* cExp, float* sExp, int thread_id, int processors );

//OpenMP Functions
void  Normal2SSBump( unsigned char *data, int height, int width, Modes mode = N_DOT_L );
void  Normal2SSBump( float3 *data, int height, int width, Modes mode = N_DOT_L );
void  Normal2Specular( unsigned char *data, int height, int width );
void  Normal2Specular( float3 *data, int height, int width );
void  Normal2DuDv( unsigned char *data, int height, int width );
void  Normal2DuDv( float3 *data, int height, int width );
void  Image2Height( unsigned char *data, int height, int width );
void  Height2Normal( float *h, float3 *dest, int height, int width );
void  Height2Normal( unsigned char *data, int height, int width, float scale = 1.0f );
void  Height2Normal( float3 *data, int height, int width, float scale = 1.0f );
void  Height2DirectionalAO( unsigned char *data, float* h, int height, int width, ray* red, \
                            ray* blue, ray* green, int rays = 300, float scale = 0.1f,      \
                            float radius = 0.1f, bool tile = true, bool h_tile = true,      \
                            bool v_tile = true, int *complete = NULL );
void  Height2DirectionalAO( float3 *data, float* h, int height, int width, ray* red,   \
                            ray* blue, ray* green, int rays = 300, float scale = 0.1f, \
                            float radius = 0.1f, bool tile = true, bool h_tile = true, \
                            bool v_tile = true, int *complete = NULL );
void  Blend( BlendType type , float percent, unsigned char *src,    \
             unsigned char *src2, unsigned char *dest, int height, int width );
void  Blend( BlendType type , float percent, float3 *src,        \
             float3 *src2, float3 *dest, int height, int width );
void  normalize( unsigned char *data, int height, int width );
void  normalize( float3 *data, int height, int width );

void  ChangeDepth(float * h, int height, int width, float amount, float scale );
void  Contrast(float * data, int height, int width, float contrast );
void  NormalScale( float3 *normal, int height, int width, float intensity );
void  BlendNormal( float percent, float3 *src, float3 *src2, float3 *dest, int height, int width );
void  NormalModulation( float3* n1, float3* n2, float3* dest, float* h1, float* h2, int height, int width );
void  NormalOverlay( float3* src1, float3* src2, float3* dest, float* h1, float* h2, int height, int width );
void  NormalEdges( float3 *normal, float *h, int height, int width, float strength, float intensity );

void  Normal2Height( float3 *normal, float *h, int height, int width );

void  Grayscale(float3 *src, float3 *dest, int height, int width );
void  Grayscale(float3 *src, float *dest, int height, int width );

void  GenerateExp(float range, float* expMatrix );
void  BilateralFilter(float *src, float *dest, int height, int width, float radius, float* cExp, float* sExp );
void  BilateralFilter(float3 *src, float3 *dest, int height, int width, float radius, float* cExp, float* sExp );

float3 make_float3(float x, float y, float z);

int MakeKernel(float* & matrix, float radius);
void Blur( float* inPixels, float* outPixels, int width, int height, float radius );
void ConvolveAndTranspose(float* matrix, float *inPixels, float *outPixels, int width, int height, int cols, int edgeAction);

#endif
