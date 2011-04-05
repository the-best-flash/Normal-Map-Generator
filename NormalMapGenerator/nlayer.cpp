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

#include "nlayer.h"

NLayer::NLayer()
{
    name = "";
    mode = 0;
    invert = false;
    blend = 100.0f;
    modified = true;
    height = 0;
    width = 0;
    baseHeight = 0;
    baseWidth = 0;

    nMap = NULL;
    baseNmap = NULL;
    h = NULL;
    baseHmap = NULL;
}

NLayer::NLayer(int _width, int _height, string _name)
{
    name = _name;
    mode = 0;
    invert = false;
    blend = 100.0f;
    modified = true;
    height = _height;
    width = _width;
    baseHeight = 0;
    baseWidth = 0;

    nMap = new float3[height * width];
    baseNmap = NULL;
    h = new float[height * width];
    baseHmap = NULL;
}

NLayer::NLayer(NLayer &n)
{
    int i;

    name = n.Name();
    mode = n.BlendMode();
    invert = n.Invert();
    blend = n.BlendAmount();
    modified = n.Modified();
    width = n.Width();
    height = n.Height();
    baseHeight = n.baseHeight;
    baseWidth = n.baseWidth;

    float3* tmp_n = n.NormalMap();
    float*  tmp_h = n.HeightMap();
    int size = width * height;

    float3 *tmp_n2 = n.BaseNormalMap();
    float *tmp_h2 = n.BaseHeightMap();
    int size2 = baseHeight * baseWidth;

    if(size != 0)
    {
        nMap = new float3[size];
        h = new float[size];
    }
    else
    {
        nMap = NULL;
        h = NULL;
    }

    if( size2 != 0 )
    {
        baseNmap = new float3[size2];
        baseHmap = new float[size2];
    }
    else
    {
        nMap = NULL;
        h = NULL;
    }

    float3 *nM, *baseN;
    float *hMap, *baseH;
    nM = nMap;
    hMap = h;
    baseN = baseNmap;
    baseH = baseHmap;

    #pragma omp parallel default(none) private(i) firstprivate(nM, hMap, baseN, baseH, tmp_n, tmp_h, tmp_n2, tmp_h2, size, size2)
    {
        char padding[128];
        padding[0] = 0;

        #pragma omp for nowait
        for(i = 0; i < size; i++)
        {
            nM[i] = tmp_n[i];
            hMap[i] = tmp_h[i];
        }

        #pragma omp for nowait
        for( i = 0; i < size2; i++ )
        {
            baseN[i] = tmp_n2[i];
            baseH[i] = tmp_h2[i];
        }
    }
}

NLayer::~NLayer()
{
    if( nMap != NULL )
        delete [] nMap;

    if( baseNmap != NULL )
        delete [] baseNmap;

    if( h != NULL )
        delete [] h;

    if( baseHmap != NULL )
        delete [] baseHmap;
}

//Setters
void NLayer::Name(string str)
{
    name = str;
}

void NLayer::BlendMode(int mode)
{
    if( mode < ADDITIVE )
        mode = ADDITIVE;
    else if( mode > NORMAL )
        mode = NORMAL;
    else
        mode = mode;
}

void NLayer::Invert(bool _invert)
{
    invert = _invert;
}

void NLayer::BlendAmount(float amount)
{
    blend = amount;
}

void NLayer::Modified(bool _modified)
{
    modified = _modified;
}

void NLayer::Height(int _height)
{
    Size(width, _height);
}

void NLayer::Width(int _width)
{
    Size(_width, height);
}

void NLayer::Size(int _width, int _height)
{
    delete [] nMap;
    delete [] h;

    width = _width;
    height = _height;

    int size = width * height;
    int row, col;
    int r, c;
    int i;
    int offset;

    if( size > 0 )
    {
        nMap = new float3[size];
        h = new float[size];

        r = c = i = 0;

        for(row = 0; row < height; row++)
        {
            if( r > baseHeight )
                r = 0;

            offset = r * baseWidth;
            c = 0;

            for( col = 0; col < width; col++)
            {
                if( c > baseWidth )
                    c = 0;

                nMap[i] = baseNmap[offset + c];
                h[i] = baseHmap[offset + c];

                c++;
                i++;
            }

            r++;
        }
    }
    else
    {
        height = width = 0;
        nMap = NULL;
        h = NULL;
    }

}

//Getters
string NLayer::Name()
{
    return name;
}

int NLayer::BlendMode()
{
    return mode;
}

bool NLayer::Invert()
{
    return invert;
}

float NLayer::BlendAmount()
{
    return blend;
}

bool NLayer::Modified()
{
    return modified;
}

int NLayer::Height()
{
    return height;
}

int NLayer::Width()
{
    return width;
}

float3* NLayer::NormalMap()
{
    return nMap;
}

float3* NLayer::BaseNormalMap()
{
    return baseNmap;
}

float* NLayer::HeightMap()
{
    return h;
}

float* NLayer::BaseHeightMap()
{
    return baseHmap;
}

//Blending
void NLayer::BlendNormal(float3* _nMap, float* _h)
{
    int i;
    int size = height * width;
    float3 n;
    float blendInverse = 1.0f - blend;
    float blendVal = blend;
    float3 *a, *b;
    a = _nMap;
    b = nMap;
    float *h1, *h2;
    h1 = _h;
    h2 = h;

    #pragma omp parallel default(none) private(i, n) firstprivate(size, a, b, blendVal, blendInverse, h1, h2)
    {
        char padding[128];
        padding[0] = 0;

        switch(mode)
        {
        case ADDITIVE:
            #pragma omp for
            for(i = 0; i < size; i++)
            {
                n = b[i];

                n.x /= n.z;
                n.y /= n.z;
                n.z = 0;

                a[i].x /= n.z;
                a[i].y /= n.z;

                a[i] = blendVal * (n + a[i]) + (blendInverse) * (a[i]);
                a[i].z = 1.0f;

                normalize(a[i]);
            }
            break;

        case OVERLAY:
            #pragma omp for
            for( i = 0; i < size; i++ )
            {
                a[i] = (a[i] + 1) / 2;

                //a = output b = input
                a[i].x = blendVal * overlay(a[i].x , ((b[i].x + 1) / 2)) + (blendInverse) * a[i].x;
                a[i].y = blendVal * overlay(a[i].y , ((b[i].y + 1) / 2)) + (blendInverse) * a[i].y;
                a[i].z = blendVal * overlay(a[i].z , ((b[i].z + 1) / 2)) + (blendInverse) * a[i].z;

                a[i] = (a[i] * 2) - 1;

                normalize(a[i]);
            }
            break;

        case MULTIPLY:
            #pragma omp for
            for( i = 0; i < size; i++ )
            {
                n = b[i];
                n.x /= n.z;
                n.y /= n.z;

                a[i].x /= a[i].z;
                a[i].y /= a[i].z;

                a[i].x = blendVal * (n.x * h1[i] + a[i].x * h2[i]) + (blendInverse) * a[i].x;
                a[i].y = blendVal * (n.y * h1[i] + a[i].y * h2[i]) + (blendInverse) * a[i].y;
                a[i].z = 1.0f;

                normalize(a[i]);
            }
            break;

        case NORMAL:
            #pragma omp for
            for( i = 0; i < size; i++ )
            {
                n = b[i];
                n.x /= n.z;
                n.y /= n.z;

                a[i].x /= a[i].z;
                a[i].y /= a[i].z;

                a[i] = blendVal * n + (blendInverse) * a[i];
                a[i].z = 1.0f;

                normalize(a[i]);
            }
            break;
        }
    }
}

void NLayer::BlendHeight(float* _h)
{
    int i;
    int size = height * width;
    float blendInverse = 1.0f - blend;
    float max = h[0], min = h[0];
    float max2 = _h[0], min2 = _h[0];
    float* hMap = h;
    float blendVal = blend;

    #pragma omp parallel default(none) private(i) firstprivate(size, _h, hMap, blendVal, blendInverse, max, min, max2, min2)
    {
        switch(mode)
        {
        case ADDITIVE:
            #pragma omp for
            for( i = 0; i < size; i++)
            {
                _h[i] = blendVal*(hMap[i] + _h[i]) + blendInverse*_h[i];
            }
            break;
        case OVERLAY:
            for( i = 0; i < size; i++)
            {
                if( hMap[0] > max )
                    max = hMap[0];

                if( hMap[0] < min )
                    min = hMap[0];

                if( _h[0] > max2 )
                    max2 = _h[0];

                if( _h[0] < min2 )
                    min2 = _h[0];
            }

            #pragma omp for
            for( i = 0; i < size; i++ )
            {
                hMap[i] = (hMap[i] + min) / max;
                _h[i] = (_h[i] + min2) / max2;

                _h[i] = blendVal*overlay(_h[i], hMap[i]) + blendInverse*_h[i];
            }
            break;
        case MULTIPLY:
            #pragma omp for
            for( i = 0; i < size; i++)
            {
                _h[i] = blendVal*(hMap[i] * _h[i]) + blendInverse*_h[i];
            }
            break;
        case NORMAL:
            #pragma omp for
            for( i = 0; i < size; i++ )
            {
                _h[i] = blendVal * hMap[i] + blendInverse*_h[i];
            }
            break;
        }
    }

    max = min = _h[0];
    for( i = 0; i < size; i++ )
    {
        if( _h[i] > max )
            max = _h[i];

        if( _h[i] < min )
            min = _h[i];
    }

    #pragma omp parallel for default(none) private(i) firstprivate(size, _h, min, max)
    for( i = 0; i < size; i++ )
    {
        _h[i] = (_h[i] + min) / max;
    }
}

NLayer& NLayer::operator=(NLayer &n)
{
    int i;

    name = n.name;
    mode = n.mode;
    invert = n.invert;
    blend = n.blend;
    modified = n.modified;
    width = n.width;
    height = n.height;
    baseHeight = n.baseHeight;
    baseWidth = n.baseWidth;

    float3* tmp_n = n.nMap;
    float*  tmp_h = n.h;
    int size = width * height;

    float3 *tmp_n2 = n.baseNmap;
    float *tmp_h2 = n.baseHmap;
    int size2 = baseHeight * baseWidth;

    if(size != 0)
    {
        nMap = new float3[size];
        h = new float[size];
    }
    else
    {
        nMap = NULL;
        h = NULL;
    }

    if( size2 != 0 )
    {
        baseNmap = new float3[size2];
        baseHmap = new float[size2];
    }
    else
    {
        nMap = NULL;
        h = NULL;
    }

    float3 *nM, *baseN;
    float *hMap, *baseH;
    nM = nMap;
    hMap = h;
    baseN = baseNmap;
    baseH = baseHmap;

    #pragma omp parallel default(none) private(i) firstprivate(nM, hMap, baseN, baseH, tmp_n, tmp_h, tmp_n2, tmp_h2, size, size2)
    {
        char padding[128];
        padding[0] = 0;

        #pragma omp for nowait
        for(i = 0; i < size; i++)
        {
            nM[i] = tmp_n[i];
            hMap[i] = tmp_h[i];
        }

        #pragma omp for nowait
        for( i = 0; i < size2; i++ )
        {
            baseN[i] = tmp_n2[i];
            baseH[i] = tmp_h2[i];
        }
    }

    return n;
}

void NLayer::LoadNLayer(ifstream &in)
{
    int i;
    int _i;
    char _c;

    modified = true;

    name = "";
    in.read((char*)&_i, sizeof(int));
    for(i = 0; i < _i; i++)
    {
        in.read(&_c, sizeof(char));
        name += _c;
    }

    in.read((char*)&height, sizeof(int));
    in.read((char*)&width, sizeof(int));
    in.read((char*)&invert, sizeof(bool));
    in.read((char*)&blend, sizeof(float));

    nMap = new float3[height * width];
    h = new float[height * width];
}

void NLayer::SaveNLayer(ofstream &out)
{
    int _i;

    _i = name.length();
    out.write((char*)&_i, sizeof(int));
    out.write(name.c_str(), name.length());

    out.write((char*)&height, sizeof(int));
    out.write((char*)&width, sizeof(int));
    out.write((char*)&invert, sizeof(bool));
    out.write((char*)&blend, sizeof(float));
}

void NLayer::StoreBaseImages()
{
    int x, y, i, j;

    x = y = 0;
    for( i = 0; i < height; i++ )
    {
        for(j = 0; j < width; j++)
        {
            nMap[i * width + j] = baseNmap[y * width + x];
            h[i * width + j] = baseHmap[y * width + x];

            x++;

            if( x > baseWidth )
                x -= baseWidth;
        }

        y++;

        if( y > baseHeight )
            y -= baseHeight;
    }
}
