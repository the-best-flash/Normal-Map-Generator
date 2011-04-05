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

#ifndef NMAP_H
#define NMAP_H

#include <string>
#include <fstream>
using namespace std;

#include "LinkedList.h"
#include "nlayer.h"
#include "normallayer.h"
#include "quadimagelayer.h"
#include "heightlayer.h"
#include "imagelayer.h"
#include "nlist.h"
#include "generatorlayer.h"

class NMap
{
public:
    NMap();
    NMap(NMap &nm);
    ~NMap();

    typedef LinkedList<NLayer*> List;
    typedef List::iterator iterator;

    void Add(NLayer* layer);
    void Remove(int pos);

    iterator At(int i);
    iterator Begin();
    iterator End();

    void GenerateAll();
    void GenerateSelected(int *selected, int n);
    void GenerateHeight();
    void SaveList(ofstream &out);
    void SaveNormal(string fileName);
    void SaveHeight(string fileName);
    void LoadList(ifstream &in);

private:
    List layer;
    int width, height;
    string name;
    float intensity;
    bool invertX, invertY;

    float3* n;
    float*  h;
};

#endif // NMAP_H
