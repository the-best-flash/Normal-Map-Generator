#ifndef NORMALLAYER_H
#define NORMALLAYER_H

#include "nlayer.h"
#include <string>
using namespace std;

class NormalLayer : public NLayer
{
public:
    NormalLayer();
    NormalLayer(const NormalLayer &nl);
    ~NormalLayer();

    virtual void Generate();
    virtual void GenerateHeight();
    virtual int  Type();
    virtual void Save(ofstream &out);
    virtual void Load(ifstream &in);

protected:
    void LoadImage(char* str);

    string image;
    float n_intensity;
};

#endif // NORMALLAYER_H
