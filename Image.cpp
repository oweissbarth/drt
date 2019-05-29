#include "Image.h"
#include <OpenImageIO/imageio.h>

OIIO_NAMESPACE_USING

Image::Image(unsigned int width, unsigned int height){
    this->pixels.resize(width*height);
    this->width = width;
    this->height = height;
}

bool Image::save(std::string path){
    ImageOutput *out = ImageOutput::create(path);
    if(!out){
        std::cerr << "could not write image"<< std::endl;
        return false;
    }
    ImageSpec spec (width, height, 4, TypeDesc::FLOAT);

    out->open(path, spec);
    out->write_image(TypeDesc::FLOAT, this->pixels.data());
    out->close();

    delete out;
    
    return true;
}
