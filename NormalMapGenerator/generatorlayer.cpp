#include "generatorlayer.h"

GeneratorLayer::GeneratorLayer()
{
    image = 0;
    n_intensity = 1.0f;
}

GeneratorLayer::GeneratorLayer(GeneratorLayer &l)
{
    image = l.image;
    n_intensity = l.n_intensity;
}

void GeneratorLayer::Generate()
{
    lst->Generate(image, baseNmap);

    NormalScale(baseNmap, baseHeight, baseWidth, n_intensity);

    this->StoreBaseImages();
}

void GeneratorLayer::GenerateHeight()
{
    lst->GenerateHeight(image, baseHmap);

    this->StoreBaseImages();
}

int  GeneratorLayer::Type()
{
    return NLayer::GENERATOR;
}

void GeneratorLayer::Save(ofstream &out)
{
    this->SaveNLayer(out);

    out.write((char*)&image, sizeof(int));
    out.write((char*)&n_intensity, sizeof(float));
}

void GeneratorLayer::Load(ifstream &in)
{
    this->LoadNLayer(in);

    in.read((char*)&image, sizeof(int));
    in.read((char*)&n_intensity, sizeof(float));
}
