#ifndef DENGI_IMG_BMP_H
#define DENGI_IMG_BMP_H

#include "../kernel.h"
#include <vector>

using namespace std;
namespace dengi{
   class ImgBMP {
        public:
            DENGIDEF ImgBMP(); //constructor
            DENGIDEF ~ImgBMP(); //destructor

            void DENGIDEF SetSize( unsigned int w, unsigned int h); //setea tamaño
            unsigned int DENGIDEF GetWidth(); //devuelve el ancho
            unsigned int DENGIDEF GetHeight(); //devuelve el alto

            void DENGIDEF SetFormat( short f); //setea el formato
            short DENGIDEF GetFormat(); //devuelve el formato

            void DENGIDEF SetDistrData( short d); //setea la distribusion de los datos en el buffer
            short DENGIDEF GetDistrData(); //devuelve la distribucion del formato

            void DENGIDEF SetBuffer( void *Ptr); //setea la direccion del buffer
            void* DENGIDEF GetBuffer(); //devuelve el buffer

            int DENGIDEF LoadFromFile(char *src);
            char DENGIDEF IsFormat(char *src);

        private:
            unsigned int width, height;
            short format;
            short distr_data;
            void *pixels;
    };
}
#endif // IMG_PNG_H
