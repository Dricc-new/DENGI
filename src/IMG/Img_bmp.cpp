#include "../../include/DENGI/Img/Img_bmp.h"
#include <stdio.h>
#define BITMAPCOREHEADER 12
#define OS22XBITMAPHEADER 16
#define OS22XBITMAPHEADER2 64
#define BITMAPV2INFOHEADER 40
#define BITMAPV3INFOHEADER 56
#define BITMAPV4HEADER 108
#define BITMAPV5HEADER 124


namespace dengi{
    DENGIDEF ImgBMP::ImgBMP(){
        width = 0;
        height = 0;
        pixels = 0;
    };

    //setea tamaño
    void DENGIDEF ImgBMP::SetSize( unsigned int w, unsigned int h){
        width  = w;
        height = h;
    }

    //devuelve el ancho
    unsigned int DENGIDEF ImgBMP::GetWidth(){
        return width;
    }

    //devuelve el alto
    unsigned int DENGIDEF ImgBMP::GetHeight(){
        return height;
    }

    //setea el formato
    void DENGIDEF ImgBMP::SetFormat( short f){
        format = f;
    }

    //devuelve el formato
    short DENGIDEF ImgBMP::GetFormat(){
        return format;
    }

    //setea la distribusion de los datos en el buffer
    void DENGIDEF ImgBMP::SetDistrData( short d){
        distr_data = d;
    }

    //devuelve la distribucion del formato
    short DENGIDEF ImgBMP::GetDistrData(){
        return distr_data;
    }

    //setea la direccion del buffer
    void DENGIDEF ImgBMP::SetBuffer( void *Ptr){
        if(pixels) delete pixels;
        pixels = Ptr;
    }

    //devuelve el buffer
    void* DENGIDEF ImgBMP::GetBuffer(){
        return pixels;
    }

    DENGIDEF ImgBMP::~ImgBMP(){
        if(pixels) delete pixels;
    }

    int DENGIDEF ImgBMP::LoadFromFile(char *src){
        //Open File
        if(pixels) delete pixels;
        FILE* file = fopen(src, "rb");
        if(file  == NULL) {
            return -1;
        }

        //File Header read
        short typefile;
        fread( &typefile, 2, 1, file);

        if(typefile != 0x4d42){
            fclose(file);
            return 0;
        }

        //Lo que queda en la cabecera del archivo
        /* HeaderData[0] File Size , HeaderData[1] Reserbado,
        HeaderData[2] distancia en bytes hasta el Array Pixels*/
        unsigned int HeaderData[3]; //
        fread( HeaderData, 4, 3, file);

        //DIB info de el tamaño de DIBInfo
        unsigned int DIBType;
        fread(&DIBType,4,1,file);
        unsigned int DIBData[(DIBType/4)-1];
        fread(&DIBData,4,(DIBType/4)-1,file);

        unsigned char channels = (DIBData[2]>>16)/8;
        unsigned int length = DIBData[0]*DIBData[1]*channels;
        //printf("-- %d --\n",length);
        printf("-- WIDTH  %d --\n",HeaderData[0]);
        printf("-- WIDTH  %d --\n",HeaderData[2]);
        printf("-- WIDTH  %d --\n",DIBData[0]);
        printf("-- HEIFHT %d --\n",DIBData[1]);
        printf("-- PANEL  %d --\n",DIBData[2]&0x0000FFFF);
        printf("-- BITCLR %d --\n",DIBData[2]>>16);
        printf("-- COMPRI %d --\n",DIBData[3]);
        printf("-- SIZE   %d --\n",DIBData[4]);
        printf("-- X %d --\n",DIBData[5]);
        printf("-- Y %d --\n",DIBData[6]);
        printf("-- C %d --\n",DIBData[7]);
        printf("-- I %d --\n",DIBData[8]);
        if(length > DIBData[4] && !DIBData[3]){
            fclose(file);
            return 2;
        }
        unsigned char buffer[length];
        unsigned char *temp = new unsigned char[length];

        switch(DIBType){
            case BITMAPCOREHEADER:
                break;
            case OS22XBITMAPHEADER:
                break;
            case OS22XBITMAPHEADER2:
                break;

            /*                      BITMAPV2INFOHEADER STRUCTURE
            DIBData[0] = width, DIBData[1] = height, DIBData[2] los dos primeros bytes son
            para cantidad de Planos y los dos ultimos para la cantidad de bit por color,
            DIBData[3] Si esta comprimida o no la imagen*/
            case BITMAPV2INFOHEADER:
                fread( buffer, 1, length, file);
                for(int i = 0; i < length; i+=channels){
                    temp[i]   = buffer[i+2];
                    temp[i+1] = buffer[i+1];
                    temp[i+2] = buffer[i];
                }
                break;
            case BITMAPV3INFOHEADER:
                break;
            case BITMAPV4HEADER:
                break;
            case BITMAPV5HEADER:
                break;
        }
        pixels = temp;
        width = DIBData[0];
        height = DIBData[1];
        format = 0x1907;
        distr_data = 0x1401;
        fclose(file);
        return 1;
    }
    char DENGIDEF ImgBMP::IsFormat(char *src){
        FILE* file = fopen(src, "rb");
        if(file  == NULL) {
            return -1;
        }
        short header;
        fread( &header, 2, 1, file);
        fclose(file);
        if(header == 0x4d42)
            return 1;
        else
            return 0;
    }
}
