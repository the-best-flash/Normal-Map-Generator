#include "heightlayer.h"

HeightLayer::HeightLayer()
{
}

void HeightLayer::Generate()
{
    this->GenerateHeight();

    float *temp_h = h;
    float3 *temp_n = nMap;
    int max = baseHeight * baseWidth;

    #pragma omp parallel for firstprivate(max, temp_n, temp_h)
    for(int i = 0; i < max; i++)
    {
        temp_n[i].x = temp_n[i].y = temp_n[i].z = temp_h[i];
    }

    Height2Normal(nMap, baseHeight, baseWidth, scale);
}

void HeightLayer::GenerateHeight()
{
    this->StoreBaseImages();

    if(blur != 0.0f)
        Blur(h, h, width, height, blur);

    if(filter != 0.0f)
    {
        float *cExp = new float[(int)ceil(filter)];
        float sExp[256] = {0};

        GenerateExp((int)ceil(filter), cExp);
        GenerateExp(128, sExp);

        BilateralFilter(h, h, height, width, filter, cExp, sExp);
    }
}

int  HeightLayer::Type()
{
    return NLayer::HEIGHT;
}

void HeightLayer::Save(ofstream &out)
{
    int _i;

    this->SaveNLayer(out);

    _i = image.length();
    out.write((char*)&_i, sizeof(int));
    out.write(image.c_str(), image.length());

    out.write((char*)&scale, sizeof(float));
    out.write((char*)&blur, sizeof(float));
    out.write((char*)&filter, sizeof(float));
}

void HeightLayer::Load(ifstream &in)
{
    int i;
    int _i;
    char _c;

    this->LoadNLayer(in);

    in.read((char*)&_i, sizeof(int));
    image.clear();
    for( i = 0; i < _i; i++)
    {
        in.read(&_c, sizeof(char));
        image += _c;
    }

    in.read((char*)&scale, sizeof(float));
    in.read((char*)&blur, sizeof(float));
    in.read((char*)&filter, sizeof(float));

    this->LoadImage((char*)image.c_str());
}

void HeightLayer::LoadImage(char* str)
{
    ilInit();

    ilEnable(IL_FILE_OVERWRITE);
    ilEnable(IL_ORIGIN_SET);
    ilSetInteger(IL_ORIGIN_SET, IL_ORIGIN_UPPER_LEFT);

    ilLoadImage( str );

    baseWidth = ilGetInteger(IL_IMAGE_WIDTH);
    baseHeight = ilGetInteger(IL_IMAGE_HEIGHT);
    int bytes  = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL) / 8;

    uchar *data;

    if( bytes > 1 )
        data = new(nothrow) uchar[baseWidth * baseHeight * 3];
    else
        data = new(nothrow) uchar[baseWidth * baseHeight];

    if( bytes > 1 )
        ilCopyPixels( 0, 0, 0, baseWidth, baseHeight, 1, IL_RGB, IL_UNSIGNED_BYTE, (void*)data );
    else
        ilCopyPixels( 0, 0, 0, baseWidth, baseHeight, 1,  IL_BYTE, IL_UNSIGNED_BYTE, (void*)data );

    baseHmap = new float[baseWidth * baseHeight];
    baseNmap = new float3[baseWidth * baseHeight];

    int max = baseWidth * baseHeight;
    float* temp_h = baseHmap;

    if(bytes > 1)
    {
        #pragma omp parallel for firstprivate(data, temp_h, max)
        for(int i = 0; i < max; i++)
        {
            temp_h[i] = data[i*3] / 255.0f;
        }
    }
    else
    {
        #pragma omp parallel for firstprivate(data, temp_h, max)
        for(int i = 0; i < max; i++)
        {
            temp_h[i] = data[i] / 255.0f;
        }
    }

    delete [] data;

    ilShutDown();
}
