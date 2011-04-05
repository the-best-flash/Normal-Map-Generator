#ifndef HEIGHTLAYER_H
#define HEIGHTLAYER_H

#include "nlayer.h"
#include <string>
using namespace std;

class HeightLayer : public NLayer
{
public:
    HeightLayer();
    HeightLayer(const HeightLayer& hl);
    ~HeightLayer();

    virtual void Generate();
    virtual void GenerateHeight();
    virtual int  Type();
    virtual void Save(ofstream &out);
    virtual void Load(ifstream &in);

protected:
    virtual void LoadImage(char* str);

    string image;
    float scale;
    float blur;
    float filter;
};

#endif // HEIGHTLAYER_H
