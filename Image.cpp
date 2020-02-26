#include "Image.h"
#include <OpenImageIO/imageio.h>
#include "utils.h"
#include <cmath>

OIIO_NAMESPACE_USING

Image::Image(unsigned int width, unsigned int height){
    this->pixels.resize(width*height);
    this->width = width;
    this->height = height;
}

bool Image::save(std::string path){
    auto out = ImageOutput::create(path);
    if(!out){
        std::cerr << "could not write image"<< std::endl;
        return false;
    }
    ImageSpec spec (width, height, 4, TypeDesc::FLOAT);

    out->open(path, spec);
    out->write_image(TypeDesc::FLOAT, this->pixels.data());
    out->close();

    return true;
}

void Image::tonemap()
{
    float Lavg = 0;
    for (unsigned int i = 0; i < pixels.size(); ++i) {
        Lavg += log(luminance(pixels[i]));
    }
    Lavg = exp(Lavg/pixels.size());


    float lum_factor = 0.f;
    for (unsigned int i = 0; i < pixels.size(); ++i) {
        lum_factor = 0.2f/Lavg*luminance(pixels[i]);

        lum_factor = lum_factor/(1.f + lum_factor);

        pixels[i] = lum_factor * pixels[i];
        pixels[i].w = 1.f;
    }
}

void Image::scale_values(float factor)
{
    for (unsigned int i = 0; i < pixels.size(); ++i) {
        float alpha = pixels[i].w;
        pixels[i] *= factor;
        pixels[i].w = alpha;
    }
}
