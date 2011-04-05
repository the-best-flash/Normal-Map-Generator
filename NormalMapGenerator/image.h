#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"
#include <cstring>

template <class _T>
class Image
{
public:
    Image<_T>()
    {
        data = NULL;
    }

    Image<_T>(Image<_T> &img)
    {
        height = img.height;
        width = img.width;

        data = new Pixel<_T>[height * width];

        int size = height * width;
        for(int i = 0; i < size; i++)
        {
            data[i] = img.data[i];
        }
    }

    Image<_T>(int w, int h)
    {
        height = h;
        width = w;

        data = new Pixel<_T>[height * width];

        memset(data, 0, sizeof(Pixel<_T>) * height * width);
    }

    Image<_T>(int w, int h, _T *d)
    {
        height = h;
        width = w;

        data = (Pixel<_T>*)d;
    }

    Image<_T>(int w, int h, Pixel<_T> *d)
    {
        height = h;
        width = w;

        data = d;
    }

    ~Image()
    {
        if(data != NULL)
            delete [] data;
    }

    Pixel<_T>* operator[](int i)
    {
        if(i < height)
            return &data[i * width];

        return NULL;
    }

    int h()
    {
        return height;
    }

    int w()
    {
        return width;
    }

    Pixel<_T>* pixels()
    {
        return data;
    }

    void ClearData()
    {
        data = NULL;
        height = 0;
        width = 0;
    }

    void Reallocate(int w, int h)
    {
        if(data != NULL)
            delete [] data;

        width = w;
        height = h;

        data = new Pixel<_T>[w * h];

        memset(data, 0, sizeof(Pixel<_T>) * h * w);
    }

    operator Image<float>()
    {
        Image<float> img(width, height);

        int size = width * height;

        float* d = img.data();
        for(int i = 0; i < size; i++)
        {
            d[i] = (Pixel<float>)data[i];
        }

        return img;
    }

    operator Image<int>()
    {
        Image<int> img(width, height);

        int size = width * height;

        int* d = img.data();
        for(int i = 0; i < size; i++)
        {
            d[i] = (Pixel<int>)data[i];
        }

        return img;
    }

    operator Image<uchar>()
    {
        Image<uchar> img(width, height);

        int size = width * height;

        uchar* d = img.data();
        for(int i = 0; i < size; i++)
        {
            d[i] = (Pixel<uchar>)data[i];
        }

        return img;
    }

private:
    Pixel<_T>* data;
    int height, width;
};

#endif // IMAGE_H
