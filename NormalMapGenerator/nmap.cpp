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

#include "nmap.h"

NMap::NMap()
{
    width = 0;
    height = 0;
    name = "";
    intensity = 1.0f;
    invertX = false;
    invertY = false;

    n = NULL;
    h = NULL;
}

NMap::NMap(NMap &nm)
{
    width = nm.width;
    height = nm.height;
    name = nm.name;
    intensity = nm.intensity;
    invertX = nm.invertX;
    invertY = nm.invertY;

    int size = width * height;
    int i;

    n = new float3[size];
    h = new float[size];

    for(i = 0; i < size; i++)
    {
        n[i] = nm.n[i];
        h[i] = nm.h[i];
    }
}

NMap::~NMap()
{
    delete [] n;
    delete [] h;
}

void NMap::Add(NLayer* nLayer)
{
    layer.push_back(nLayer);
}

void NMap::Remove(int pos)
{
    layer.remove(pos);
}

NMap::iterator NMap::At(int i)
{
    return layer.at(i);
}

NMap::iterator NMap::Begin()
{
    return layer.begin();
}

NMap::iterator NMap::End()
{
    return layer.end();
}

void NMap::GenerateAll()
{ 
    int i;
    float3 *_n;
    float  *_h;
    int size = height * width;

    for(NMap::iterator it = layer.begin(); it != layer.end(); ++it)
    {
        it.Get()->Generate();
        it.Get()->GenerateHeight();

        if( it == layer.begin() )
        {
            _n = it.Get()->NormalMap();
            _h = it.Get()->HeightMap();

            for(i = 0; i < size; i++)
            {
                n[i] = _n[i];
                h[i] = _h[i];
            }
        }
        else
        {
            it.Get()->BlendNormal(n, h);
            it.Get()->BlendHeight(h);
        }
    }
}

void NMap::GenerateSelected(int *selected, int num)
{
    int i;
    float3 *_n;
    float  *_h;
    int size = height * width;

    for( i = 0; i < num; i++ )
    {
        layer[selected[i]]->Generate();

        if( i == 0 )
        {
            _n = layer[selected[i]]->NormalMap();
            _h = layer[selected[i]]->HeightMap();

            for(i = 0; i < size; i++)
            {
                n[i] = _n[i];
                h[i] = _h[i];
            }
        }
        else
        {
            layer[selected[i]]->BlendNormal(n, h);
            layer[selected[i]]->BlendHeight(h);
        }
    }
}

void NMap::GenerateHeight()
{
    int i;
    float *_h;
    int size = height * width;

    for(NMap::iterator it = layer.begin(); it != layer.end(); ++it)
    {
        it.Get()->GenerateHeight();

        if( it == layer.begin() )
        {
            _h = it.Get()->HeightMap();

            for(i = 0; i < size; i++)
            {
                h[i] = _h[i];
            }
        }
        else
        {
            it.Get()->BlendHeight(h);
        }
    }
}

void NMap::SaveList(ofstream &out)
{
    int _i;

    _i = layer.Size();
    out.write((char*)&_i, sizeof(int));
    for(NMap::iterator it = layer.begin(); it != layer.end(); ++it)
    {
        _i = (*it)->Type();
        out.write((char*)&_i, sizeof(int));
        (*it)->Save(out);
    }
}

void NMap::SaveNormal(string fileName)
{

}

void NMap::SaveHeight(string fileName)
{

}

void NMap::LoadList(ifstream &in)
{
    int i;
    int type = 0;
    int size;
    NLayer* layer;

    in.read((char*)&size, sizeof(int));

    for(i = 0; i < size; i++)
    {
        in.read((char*)type, sizeof(int)); //Get Type

        switch(type)
        {
        case NLayer::HEIGHT:
            layer = new HeightLayer;
            layer->Load(in);
            this->Add(layer);
            break;

        case NLayer::IMAGE:
            layer = new ImageLayer;
            layer->Load(in);
            this->Add(layer);
            break;

        case NLayer::NORMAL_MAP:
            layer = new NormalLayer;
            layer->Load(in);
            this->Add(layer);
            break;

        case NLayer::QUAD_IMAGE:
            layer = new QuadImageLayer;
            layer->Load(in);
            this->Add(layer);
            break;

        case NLayer::GENERATOR:
            layer = new GeneratorLayer;
            layer->Load(in);
            this->Add(layer);
            break;
        }
    }
}
