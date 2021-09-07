#include "Img_png.h"

#include <png.h>
namespace dengi{
    DENGIDEF ImgPNG::ImgPNG(){
        width = 0;
        height = 0;
        pixels = 0;
    };

    //setea tamaño
    void DENGIDEF ImgPNG::SetSize( unsigned int w, unsigned int h){
        width  = w;
        height = h;
    }

    //devuelve el ancho
    unsigned int DENGIDEF ImgPNG::GetWidth(){
        return width;
    }

    //devuelve el alto
    unsigned int DENGIDEF ImgPNG::GetHeight(){
        return height;
    }

    //setea el formato
    void DENGIDEF ImgPNG::SetFormat( short f){
        format = f;
    }

    //devuelve el formato
    short DENGIDEF ImgPNG::GetFormat(){
        return format;
    }

    //setea la distribusion de los datos en el buffer
    void DENGIDEF ImgPNG::SetDistrData( short d){
        distr_data = d;
    }

    //devuelve la distribucion del formato
    short DENGIDEF ImgPNG::GetDistrData(){
        return distr_data;
    }

    //setea la direccion del buffer
    void DENGIDEF ImgPNG::SetBuffer( void *Ptr){
        if(pixels) delete pixels;
        pixels = Ptr;
    }

    //devuelve el buffer
    void* DENGIDEF ImgPNG::GetBuffer(){
        return pixels;
    }

    DENGIDEF ImgPNG::~ImgPNG(){
        if(pixels) delete pixels;
    }

    int DENGIDEF ImgPNG::LoadFromFile(char *src){

        size_t i,j,c;
        FILE *file = fopen( src, "rb");//Cargo el archivo
        if( !file) return 1;//Si no se pudo Abrir el archivo devuelve 1

        png_byte header[8]; //variable que contendra el encabezado del archivo PNG
        fread( header, 1, 8, file); //introduce los bits de encabezado en header

        if( png_sig_cmp( header, 0, 8)){
            fclose( file);
            return 2;
        } //si el archivo no es un PNG devuelve 2

        png_structp png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); //crea la esctructura de lectura del archivo
        if( !png_ptr){
            fclose( file);
            return 3;
        }//si no se pudo crear devuelve 3

        png_infop info_ptr = png_create_info_struct( png_ptr); //crea la esctructura de informacion del archivo
        //sino se pudo crear destruye la estructura de lectura, cierra el archivo y devuelve 4
        if( !info_ptr){
            png_destroy_read_struct( &png_ptr, NULL, NULL);
            fclose( file);
            return 4;
        }

        /*En caso de algun otro error libpng llamara a esta seccion para
        manejar dicho error, aqui se destruiran las estructuras de lectura
        y de informacion; se cerrara el archivo y retornara 5*/
        if( setjmp( png_jmpbuf(png_ptr))){
            png_destroy_read_struct( &png_ptr, &info_ptr, ( png_infopp)0);
            fclose( file);
            return 5;
        }

        png_init_io( png_ptr, file); //establese la relacion del archivo con la estructura de lectura
        png_set_sig_bytes( png_ptr, 8); //salta los archivos que fueron leidos al principio
        png_read_info( png_ptr, info_ptr); //lee la imagen png

        //establece el ancho y el alto de la imagen
        width  = png_get_image_width( png_ptr, info_ptr);
        height = png_get_image_height( png_ptr, info_ptr);

        png_uint_32 bit_depth = png_get_bit_depth ( png_ptr, info_ptr ); //bits por canal
        png_uint_32 chanels = png_get_channels ( png_ptr, info_ptr); //Número de canales
        png_uint_32 color_type = png_get_color_type ( png_ptr, info_ptr ); //Tipo de color

        //damos el formato de color a Img dependiendo del tipo de color del PNG
        switch ( color_type ) {
            // Si el color es indexado cambiamos a el color para que sea RGB
            case PNG_COLOR_TYPE_PALETTE :{
                png_set_palette_to_rgb(png_ptr) ;
                chanels = 3 ;
                format = 0x1907;
                break;
            }

            case PNG_COLOR_TYPE_RGB :{
                format = 0x1907;
                break;
            }

            case PNG_COLOR_TYPE_RGBA :{
                format = 0x1908;
                break;
            }
            case PNG_COLOR_TYPE_GRAY :{
                if ( bit_depth < 8 ){
                    png_set_expand_gray_1_2_4_to_8 ( png_ptr );
                    bit_depth = 8 ;
                }
                format = 0x1909;
                break ;
            }

            case PNG_COLOR_TYPE_GRAY_ALPHA :{
                format = 0x190A;
                break ;
            }
        }

        if(png_get_valid(png_ptr, info_ptr,PNG_INFO_tRNS)){
            png_set_tRNS_to_alpha(png_ptr);
            format = 0x1908;
            chanels++;
        }

        png_read_update_info ( png_ptr, info_ptr );
        unsigned char *rowPtrs[height];
        unsigned int widthSize = png_get_rowbytes(png_ptr, info_ptr);
        for(i = 0 ; i < height ; i ++ ) {
            rowPtrs [ i ] = new unsigned char [widthSize] ;
        }

        png_read_image ( png_ptr, rowPtrs ) ;
        fclose(file);
        if (pixels) delete pixels;
        if(bit_depth==8){
            distr_data = 0x1401;
            unsigned char *buffer = new unsigned char[height * width * chanels];
            for(i = 0; i < height; i++){
                for(j = 0; j < width; j++){
                    for(c = 0; c < chanels; c++){
                        buffer[(i*width+j)*chanels+c] = rowPtrs[(height-1)-i][j*chanels+c];
                    }
                }
            }
            pixels = buffer;
        }else if(bit_depth==16){
            distr_data = 0x1403;
            short mask;
            unsigned short *buffer = new unsigned short[height * width * chanels];
            for(i = 0; i < height; i++){
                for(j = 0; j < width; j++){
                    for(c = 0; c < chanels; c++){
                        mask = rowPtrs[(height-1)-i][j*chanels*2+c*2];
                        buffer[(i*width+j)*chanels+c] = (mask<<8)|rowPtrs[(height-1)-i][2*j*chanels+c*2+1];
                    }
                }
            }
            pixels = buffer;
        }

        return 0;
    }
}
