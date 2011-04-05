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

#ifndef NLAYER_H
#define NLAYER_H

#include <string>
#include <fstream>
#include <omp.h>
using namespace std;

#include "ImageProcessing/TextureMaster.h"
#include "IL/il.h"

class NLayer
{
protected:
    enum BlendingMode{ADDITIVE, OVERLAY, MULTIPLY, NORMAL};
public:
    NLayer();
    NLayer(int width, int height, string str = "");
    NLayer(NLayer &n);
    ~NLayer();

    virtual void Generate() = 0;
    virtual void GenerateHeight() = 0;
    virtual int  Type() = 0;
    virtual void Save(ofstream &out) = 0;
    virtual void Load(ifstream &in) = 0;

    //Setters
    void Name(string str);
    void BlendMode(int mode);
    void Invert(bool invert);
    void BlendAmount(float amount);
    void Modified(bool modified);
    void Height(int height);
    void Width(int width);
    void Size(int width, int height);

    //Getters
    string Name();
    int BlendMode();
    bool Invert();
    float BlendAmount();
    bool Modified();
    int Height();
    int Width();
    float3* NormalMap();
    float3* BaseNormalMap();
    float* HeightMap();
    float* BaseHeightMap();

    //Blending
    void BlendNormal(float3* _nMap, float* _h);
    void BlendHeight(float* h);

    NLayer& operator=(NLayer &n);

    enum LayerType{HEIGHT, IMAGE, NORMAL_MAP, QUAD_IMAGE, GENERATOR};

protected:
    void SaveNLayer(ofstream &out);
    void LoadNLayer(ifstream &in);

    void StoreBaseImages();

    string name;
    int mode;
    bool invert;
    float blend;
    bool modified;
    int height;
    int width;
    int baseHeight;
    int baseWidth;

    float3* nMap;
    float3* baseNmap; //This is used for storing the native resoultion Normal Map
    float* h;
    float* baseHmap;
};

#endif // NLAYER_H
