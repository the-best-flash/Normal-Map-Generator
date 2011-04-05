#ifndef IMAGELAYER_H
#define IMAGELAYER_H

#include "nlayer.h"
#include "heightlayer.h"

class ImageLayer : public HeightLayer
{
public:
    ImageLayer();
    ImageLayer(const ImageLayer &il);
    ~ImageLayer();

    virtual int  Type();
    virtual void LoadImage(char* str);
};

#endif // IMAGELAYER_H
