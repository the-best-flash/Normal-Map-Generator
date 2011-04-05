#include "normallayer.h"

NormalLayer::NormalLayer()
{
}

void NormalLayer::Generate()
{

}

void NormalLayer::GenerateHeight()
{

}

int  NormalLayer::Type()
{
    return NLayer::NORMAL_MAP;
}

void NormalLayer::Save(ofstream &out)
{
    int _i;

    this->SaveNLayer(out);

    _i = image.length();
    out.write((char*)&_i, sizeof(int));
    out.write(image.c_str(), image.length());

    out.write((char*)&n_intensity, sizeof(float));
}

void NormalLayer::Load(ifstream &in)
{
    int i, _i;
    char _c;

    this->LoadNLayer(in);

    in.read((char*)&_i, sizeof(int));
    image.clear();
    for(i = 0; i < _i; i++)
    {
        in.read(&_c, sizeof(char));
        image += _c;
    }

    in.read((char*)&n_intensity, sizeof(float));

    this->LoadImage((char*)image.c_str());
}

void NormalLayer::LoadImage(char* str)
{

}
