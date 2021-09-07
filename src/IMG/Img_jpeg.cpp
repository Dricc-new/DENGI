#include "../../include/DENGI/Img/Img_jpeg.h"
#include <stdio.h>

#include <png.h>
#include <jpeglib.h>

namespace dengi{
    DENGIDEF ImgJPEG::ImgJPEG(){
        width = 0;
        height = 0;
        pixels = 0;
    };

    //setea tamaño
    void DENGIDEF ImgJPEG::SetSize( unsigned int w, unsigned int h){
        width  = w;
        height = h;
    }

    //devuelve el ancho
    unsigned int DENGIDEF ImgJPEG::GetWidth(){
        return width;
    }

    //devuelve el alto
    unsigned int DENGIDEF ImgJPEG::GetHeight(){
        return height;
    }

    //setea el formato
    void DENGIDEF ImgJPEG::SetFormat( short f){
        format = f;
    }

    //devuelve el formato
    short DENGIDEF ImgJPEG::GetFormat(){
        return format;
    }

    //setea la distribusion de los datos en el buffer
    void DENGIDEF ImgJPEG::SetDistrData( short d){
        distr_data = d;
    }

    //devuelve la distribucion del formato
    short DENGIDEF ImgJPEG::GetDistrData(){
        return distr_data;
    }

    //setea la direccion del buffer
    void DENGIDEF ImgJPEG::SetBuffer( void *Ptr){
        if(pixels) delete pixels;
        pixels = Ptr;
    }

    //devuelve el buffer
    void* DENGIDEF ImgJPEG::GetBuffer(){
        return pixels;
    }

    DENGIDEF ImgJPEG::~ImgJPEG(){
        if(pixels) delete pixels;
    }


    struct my_error_mgr {
        struct jpeg_error_mgr pub;	/* "public" fields */
        jmp_buf setjmp_buffer;	/* for return to caller */
    };

    typedef struct my_error_mgr * my_error_ptr;

    void my_error_exit (j_common_ptr cinfo)
    {
    /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
        my_error_ptr myerr = (my_error_ptr) cinfo->err;

    /* Always display the message. */
    /* We could postpone this until after returning, if we chose. */
    (*cinfo->err->output_message) (cinfo);

    /* Return control to the setjmp point */
    longjmp(myerr->setjmp_buffer, 1);
    }

    int DENGIDEF ImgJPEG::LoadFromFile(char *src){
        struct jpeg_decompress_struct cinfo;
        struct my_error_mgr jerr;
        /* More stuff */
        FILE * infile;		/* source file */
        unsigned char *buffer;		/* Output row buffer */
        int row_stride;		/* physical row width in output buffer */

        if((infile = fopen(src, "rb")) == NULL) {
            return 1;
        }

        cinfo.err = jpeg_std_error(&jerr.pub);
        jerr.pub.error_exit = my_error_exit;

        if (setjmp(jerr.setjmp_buffer)) {
            jpeg_destroy_decompress(&cinfo);
            fclose(infile);
            return 2;
        }

        jpeg_create_decompress(&cinfo);

        jpeg_stdio_src(&cinfo, infile);

        (void) jpeg_read_header(&cinfo, TRUE);
        (void) jpeg_start_decompress(&cinfo);

        row_stride = cinfo.output_width * cinfo.output_components;

        png_bytep *rowPtrs = NULL ;

        rowPtrs = new png_bytep[cinfo.output_height] ;
        buffer = new unsigned char[cinfo.output_width * cinfo.output_components * cinfo.output_height];
        JSAMPROW ptr = buffer;
        ptr += (cinfo.output_height-1) * row_stride;

        while (cinfo.output_scanline < cinfo.output_height) {
            (void)jpeg_read_scanlines(&cinfo, &ptr, 1);
            ptr-=row_stride;
        }

        pixels = buffer;
        width = cinfo.output_width;
        height = cinfo.output_height;
        format = 0x1907;
        distr_data = 0x1401;

        (void)jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return 0;
    }
}
