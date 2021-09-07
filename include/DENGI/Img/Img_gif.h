#ifndef DENGI_IMG_GIF_H
#define DENGI_IMG_GIF_H

#include "../kernel.h"
#include <vector>

using namespace std;
namespace dengi{
   class ImgGIF {
        public:
            DENGIDEF ImgGIF(); //constructor
            DENGIDEF ~ImgGIF(); //destructor

            bool Blend = true;

            void DENGIDEF SetSize( unsigned int w, unsigned int h); //setea tamaño
            unsigned int DENGIDEF GetWidth(); //devuelve el ancho
            unsigned int DENGIDEF GetHeight(); //devuelve el alto

            void DENGIDEF SetFormat( short f); //setea el formato
            short DENGIDEF GetFormat(); //devuelve el formato

            void DENGIDEF SetDistrData( short d); //setea la distribusion de los datos en el buffer
            short DENGIDEF GetDistrData(); //devuelve la distribucion del formato

            void DENGIDEF SetBuffer( void *Ptr); //setea la direccion del buffer
            void* DENGIDEF GetBuffer(); //devuelve el buffer
            void* DENGIDEF GetBuffer(unsigned int num); //devuelve el buffer

            int DENGIDEF LoadFromFile(char *src);
            unsigned int DENGIDEF GetNumImgs();
            unsigned int DENGIDEF GetTimeFotogram(unsigned int fotogram);
        private:
            unsigned int width, height;
            short format;
            short distr_data;
            unsigned char **pixels;
            unsigned int *timeFotogram;
            unsigned int imgCount;

    };
}
#endif // IMG_PNG_H
