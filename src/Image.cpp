#include "../include/DENGI/Image.h"
#include "../include/DENGI/dengi.h"
#include <SFML/Graphics/Image.hpp>

namespace dengi{
    DENGIDEF Image::Image(){
        width = 0;
        height = 0;
    };

    //setea tamaño
    void DENGIDEF Image::SetSize( unsigned int w, unsigned int h){
        width  = w;
        height = h;
    }

    //devuelve el ancho
    unsigned int DENGIDEF Image::GetWidth(){
        return width;
    }

    //devuelve el alto
    unsigned int DENGIDEF Image::GetHeight(){
        return height;
    }

    //setea el formato
    void DENGIDEF Image::SetFormat( short f){
        format = f;
    }

    //devuelve el formato
    short DENGIDEF Image::GetFormat(){
        return format;
    }

    //setea la distribusion de los datos en el buffer
    void DENGIDEF Image::SetDistrData( short d){
        distr_data = d;
    }

    //devuelve la distribucion del formato
    short DENGIDEF Image::GetDistrData(){
        return distr_data;
    }

    //setea la direccion del buffer
    void DENGIDEF Image::SetBuffer( void *Ptr){

    }

    //devuelve el buffer
    void* DENGIDEF Image::GetBuffer(){
        return pixels.data();
    }

    DENGIDEF Image::~Image(){
        if(pixels.empty()) pixels.clear();
    }

    int DENGIDEF Image::LoadFromFile(char *src){
        if(pixels.empty()) pixels.clear();
#  ifndef DENGI_BUILD
        sf::Image img;
        if(!img.loadFromFile(src))
            return 1;

        sf::Color colo;

        width  = (unsigned int)img.getSize().x;
        height = (unsigned int)img.getSize().y;
        format = 0x1908;
                distr_data = 0x1401;
        for(unsigned int i = height-1; i>0 ;i--){
            for(unsigned int j = 0; j < width; j++){
                colo = img.getPixel(j,i);
                pixels.push_back(colo.r);
                pixels.push_back(colo.g);
                pixels.push_back(colo.b);
                pixels.push_back(colo.a);
            }
        }

#  endif // DENGI_BUILD
        return 0;
    }
}

