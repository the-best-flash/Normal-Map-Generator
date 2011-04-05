#ifndef QUADIMAGELAYER_H
#define QUADIMAGELAYER_H

#include "nlayer.h"
#include <string>
using namespace std;

class QuadImageLayer : public NLayer
{
public:
    QuadImageLayer();
    QuadImageLayer(const QuadImageLayer &qi);
    ~QuadImageLayer();

    virtual void Generate();
    virtual void GenerateHeight();
    virtual int  Type();
    virtual void Save(ofstream &out);
    virtual void Load(ifstream &in);

protected:
    void LoadImage(float* dest, char* src);

    float n_intensity;
    string up;
    string down;
    string left;
    string right;
    float brightness;
    float contrast;
    float blur;
    float filter;

    float *f_up, *f_down, *f_left, *f_right;
};

#endif // QUADIMAGELAYER_H
