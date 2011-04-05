#ifndef PIXEL_H
#define PIXEL_H

typedef unsigned char uchar;

template <class _T>
class Pixel
{
public:
    Pixel<_T>()
    {

    }

    Pixel<_T>(_T R, _T G, _T B)
    {
        r = R;
        g = G;
        b = B;
    }

    Pixel<_T>(_T c)
    {
        r = c;
        g = c;
        b = c;
    }

    _T operator[](int i)
    {
        switch(i)
        {
        case 0:
            return r;

        case 1:
            return g;

        case 2:
            return b;

        default:
            return 0;
        }
    }


    Pixel<_T> operator+(Pixel<_T> &p)
    {
        return Pixel<_T>(r + p.r, g + p.g, b + p.b);
    }

    Pixel<_T> operator-(Pixel<_T> &p)
    {
        return Pixel<_T>(r - p.r, g - p.g, b - p.b);
    }

    Pixel<_T> operator/(Pixel<_T> &p)
    {
        return Pixel<_T>(r / p.r, g / p.g, b / p.b);
    }

    Pixel<_T> operator*(Pixel<_T> &p)
    {
        return Pixel<_T>(r * p.r, g * p.g, b * p.b);
    }


    Pixel<_T>& operator+=(Pixel<_T> &p)
    {
        r += p.r;
        g += p.g;
        b += p.b;

        return this;
    }

    Pixel<_T>& operator-=(Pixel<_T> &p)
    {
        r -= p.r;
        g -= p.g;
        b -= p.b;

        return this;
    }

    Pixel<_T>& operator/=(Pixel<_T> &p)
    {
        r /= p.r;
        g /= p.g;
        b /= p.b;

        return this;
    }

    Pixel<_T>& operator*=(Pixel<_T> &p)
    {
        r *= p.r;
        g *= p.g;
        b *= p.b;

        return this;
    }


    Pixel<_T> operator+(int c)
    {
        return Pixel<_T>(r + c, g + c, b + c);
    }

    Pixel<_T> operator-(int c)
    {
        return Pixel<_T>(r - c, g - c, b - c);
    }

    Pixel<_T> operator/(int c)
    {
        return Pixel<_T>(r / c, g / c, b / c);
    }

    Pixel<_T> operator*(int c)
    {
        return Pixel<_T>( r * c, g * c, b * c);
    }

    Pixel<_T>& operator+=(int c)
    {
        r += c;
        g += c;
        b += c;

        return this;
    }

    Pixel<_T>& operator-=(int c)
    {
        r -= c;
        g -= c;
        b -= c;

        return this;
    }

    Pixel<_T>& operator/=(int c)
    {
        r /= c;
        g /= c;
        b /= c;

        return this;
    }

    Pixel<_T>& operator*=(int c)
    {
        r *= c;
        g *= c;
        b *= c;

        return this;
    }

    Pixel<_T> operator+(float c)
    {
        return Pixel<_T>(r + c, g + c, b + c);
    }

    Pixel<_T> operator-(float c)
    {
        return Pixel<_T>(r - c, g - c, b - c);
    }

    Pixel<_T> operator/(float c)
    {
        return Pixel<_T>(r / c, g / c, b / c);
    }

    Pixel<_T> operator*(float c)
    {
        return Pixel<_T>(r * c, g * c, b * c);
    }

    Pixel<_T>& operator+=(float c)
    {
        r += c;
        g += c;
        b += c;

        return this;
    }

    Pixel<_T>& operator-=(float c)
    {
        r -= c;
        g -= c;
        b -= c;

        return this;
    }

    Pixel<_T>& operator/=(float c)
    {
        r /= c;
        g /= c;
        b /= c;

        return this;
    }

    Pixel<_T>& operator*=(float c)
    {
        r *= c;
        g *= c;
        b *= c;

        return this;
    }

    operator Pixel<float>()
    {
        Pixel<float> p;

        p.r = (float)r;
        p.g = (float)g;
        p.b = (float)b;

        return p;
    }

    operator Pixel<int>()
    {
        Pixel<int> p;

        p.r = (int)r;
        p.g = (int)g;
        p.b = (int)b;

        return p;
    }

    operator Pixel<uchar>()
    {
        Pixel<uchar> p;

        p.r = (uchar)r;
        p.g = (uchar)g;
        p.b = (uchar)b;

        return p;
    }

    _T r, g, b;
};

#endif // PIXEL_H
