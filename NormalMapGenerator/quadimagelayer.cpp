#include "quadimagelayer.h"

QuadImageLayer::QuadImageLayer()
{
    f_up = f_down = f_right = f_left = NULL;
}

void QuadImageLayer::Generate()
{

}

void QuadImageLayer::GenerateHeight()
{

}

int  QuadImageLayer::Type()
{
    return NLayer::QUAD_IMAGE;
}

void QuadImageLayer::Save(ofstream &out)
{
    int _i;

    this->SaveNLayer(out);

    _i = up.length();
    out.write((char*)&_i, sizeof(int));
    out.write(up.c_str(), up.length());

    _i = down.length();
    out.write((char*)&_i, sizeof(int));
    out.write(down.c_str(), down.length());

    _i = left.length();
    out.write((char*)&_i, sizeof(int));
    out.write(left.c_str(), left.length());

    _i = right.length();
    out.write((char*)&_i, sizeof(int));
    out.write(right.c_str(), right.length());

    out.write((char*)&n_intensity, sizeof(float));
    out.write((char*)&brightness, sizeof(float));
    out.write((char*)&contrast, sizeof(float));
    out.write((char*)&blur, sizeof(float));
    out.write((char*)&filter, sizeof(float));
}

void QuadImageLayer::Load(ifstream &in)
{
    int i, _i;
    char _c;

    this->LoadNLayer(in);

    in.read((char*)&_i, sizeof(int));
    up.clear();
    for( i = 0; i < _i; i++)
    {
        in.read(&_c, sizeof(char));
        up += _c;
    }

    in.read((char*)&_i, sizeof(int));
    down.clear();
    for( i = 0; i < _i; i++)
    {
        in.read(&_c, sizeof(char));
        down += _c;
    }

    in.read((char*)&_i, sizeof(int));
    left.clear();
    for( i = 0; i < _i; i++)
    {
        in.read(&_c, sizeof(char));
        left += _c;
    }

    in.read((char*)&_i, sizeof(int));
    right.clear();
    for( i = 0; i < _i; i++)
    {
        in.read(&_c, sizeof(char));
        right += _c;
    }

    in.read((char*)&n_intensity, sizeof(float));
    in.read((char*)&brightness, sizeof(float));
    in.read((char*)&contrast, sizeof(float));
    in.read((char*)&blur, sizeof(float));
    in.read((char*)&filter, sizeof(float));

    this->LoadImage(f_up, (char*)up.c_str());
    this->LoadImage(f_down, (char*)down.c_str());
    this->LoadImage(f_left, (char*)left.c_str());
    this->LoadImage(f_right, (char*)right.c_str());
}

void QuadImageLayer::LoadImage(float* dest, char* src)
{

}
