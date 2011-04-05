#include "nlayer.h"
#include "nlist.h"

#ifndef GENERATORLAYER_H
#define GENERATORLAYER_H

class GeneratorLayer : public NLayer
{
public:
    GeneratorLayer();
    GeneratorLayer(GeneratorLayer &l);

    virtual void Generate();
    virtual void GenerateHeight();
    virtual int  Type();
    virtual void Save(ofstream &out);
    virtual void Load(ifstream &in);

protected:
    int image;
    float n_intensity;
    NList *lst;
};

#endif // GENERATORLAYER_H
