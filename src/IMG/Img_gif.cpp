#include "../../include/DENGI/Img/Img_gif.h"
#include <stdio.h>
#define boolean int
#include <stdlib.h>
#include <gif_lib.h>
#include <ctype.h>
#include <stdbool.h>
#include <fcntl.h>

void printfbinari(unsigned char num){
    unsigned char mask = 0x01;
    printf("num binary ");
    for(int i = 7; i >= 0 ;i--){
        printf("%d",(num>>(i))&mask);
    }
    printf("\n");
}
namespace dengi{
    DENGIDEF ImgGIF::ImgGIF(){
        width = 0;
        height = 0;
        imgCount = 0;
        pixels = 0;
        format = 0;
    };

    //setea tamaño
    void DENGIDEF ImgGIF::SetSize( unsigned int w, unsigned int h){
        width  = w;
        height = h;
    }

    //devuelve el ancho
    unsigned int DENGIDEF ImgGIF::GetWidth(){
        return width;
    }

    //devuelve el alto
    unsigned int DENGIDEF ImgGIF::GetHeight(){
        return height;
    }

    //setea el formato
    void DENGIDEF ImgGIF::SetFormat( short f){
        format = f;
    }

    //devuelve el formato
    short DENGIDEF ImgGIF::GetFormat(){
        return format;
    }

    //setea la distribusion de los datos en el buffer
    void DENGIDEF ImgGIF::SetDistrData( short d){
        distr_data = d;
    }

    //devuelve la distribucion del formato
    short DENGIDEF ImgGIF::GetDistrData(){
        return distr_data;
    }

    //setea la direccion del buffer
    void DENGIDEF ImgGIF::SetBuffer( void *Ptr){
        /*if(pixels) delete pixels;
        pixels = Ptr;*/
    }

    //devuelve el buffer
    void* DENGIDEF ImgGIF::GetBuffer(){
        return *pixels;
    }

    void* DENGIDEF ImgGIF::GetBuffer(unsigned int num){
        return pixels[num];
    }

    unsigned int DENGIDEF ImgGIF::GetNumImgs(){
        return imgCount;
    }

    unsigned int DENGIDEF ImgGIF::GetTimeFotogram(unsigned int fotogram){
        return timeFotogram[fotogram];
    }

    DENGIDEF ImgGIF::~ImgGIF(){
        if(imgCount){
            for(int i = 0; i < imgCount; i++){
                delete pixels[i];
            }
            delete pixels;
            if(!timeFotogram)delete timeFotogram;
        }
    }

    int DENGIDEF ImgGIF::LoadFromFile(char *src){
        int	i, j,n=0, Size, Row, Col, Width, Height, ExtCode, Count;
        GifRecordType RecordType;
        GifByteType *Extension;
        GifRowType *ScreenBuffer;
        GifFileType *GifFile;
                GraphicsControlBlock GCB;
        int
        InterlacedOffset[] = { 0, 4, 2, 1 }, /* The way Interlaced image should. */
        InterlacedJumps[] = { 8, 8, 4, 2 };    /* be read - offsets and jumps... */
        int Error;
        ColorMapObject *ColorMap;
        if(imgCount){
            format = 0;
            for(i = 0; i < imgCount; i++){
                delete pixels[i];
            }
            delete pixels;
            if(!timeFotogram)delete timeFotogram;
        }

        if ((GifFile = DGifOpenFileName(src , &Error)) == NULL) {
            printf("Use Disponse %s",GifErrorString(Error));
            return Error;
        }
        width = GifFile->SWidth;
        height = GifFile->SHeight;
        distr_data = 0x1401;
        ScreenBuffer = (GifRowType *)malloc(GifFile->SHeight * sizeof(GifRowType));


        Size = GifFile->SWidth * sizeof(GifPixelType);/* Size in bytes one row.*/
        ScreenBuffer[0] = (GifRowType) malloc(Size); /* First row. */


        for (i = 0; i < GifFile->SWidth; i++)  /* Set its color to BackGround. */
            ScreenBuffer[0][i] = GifFile->SBackGroundColor;
        for (i = 1; i < GifFile->SHeight; i++) {
        /* Allocate the other rows, and set their color to background too: */
            if ((ScreenBuffer[i] = (GifRowType) malloc(Size)) == NULL)
                return 0;

                memcpy(ScreenBuffer[i], ScreenBuffer[0], Size);
        }

        vector<unsigned char*> Imgs;
        vector<int> Times = {0};
        GifRowType GifRow;
        GifColorType *ColorMapEntry;
        unsigned char *Buffer;
        /* Scan the content of the GIF file and load the image(s) in: */
        do {

            if (DGifGetRecordType(GifFile, &RecordType) == GIF_ERROR) {
                return GifFile->Error;
            }
            switch (RecordType) {
                case IMAGE_DESC_RECORD_TYPE:
                    if (DGifGetImageDesc(GifFile) == GIF_ERROR) {
                        return GifFile->Error;
                    }
                    Row = GifFile->Image.Top; /* Image Position relative to Screen. */
                    Col = GifFile->Image.Left;
                    Width = GifFile->Image.Width;
                    Height = GifFile->Image.Height;
                    if (GifFile->Image.Left + GifFile->Image.Width > GifFile->SWidth ||GifFile->Image.Top + GifFile->Image.Height > GifFile->SHeight) {
                        return GifFile->Error;
                    }
                    if (GifFile->Image.Interlace) {
                        /* Need to perform 4 passes on the images: */
                        for (Count = i = 0; i < 4; i++)
                            for (j = Row + InterlacedOffset[i]; j < Row + Height; j += InterlacedJumps[i]) {
                                Count++;
                                if (DGifGetLine(GifFile, &ScreenBuffer[j][Col],Width) == GIF_ERROR) {
                                    return GifFile->Error;
                                }
                            }
                    }else {
                        for (i = 0; i < Height; i++) {
                            if (DGifGetLine(GifFile, &ScreenBuffer[Row++][Col],Width) == GIF_ERROR) {
                                return GifFile->Error;
                            }
                        }
                    }
                    ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap: GifFile->SColorMap);
                    if (ColorMap == NULL) {
                        return GifFile->Error;
                    }

                    if(format == 0 ){
                        if(GCB.TransparentColor == -1||GCB.UserInputFlag){
                            format = 0x1907;
                        }else{
                            format = 0x1908;
                        }
                    }

                    if(GCB.UserInputFlag){
                        switch(GCB.DisposalMode){
                            case DISPOSAL_UNSPECIFIED:
                                break;
                            case DISPOSE_DO_NOT:
                                Blend  = false;
                                break;
                            case DISPOSE_BACKGROUND:
                                Blend  = false;
                                break;
                            case DISPOSE_PREVIOUS:
                                Blend = true;
                                break;
                        }
                    }
                    if(format == 0x1908){
                        Buffer = new unsigned char[GifFile->SHeight*GifFile->SWidth*4];
                        for (i = 0; i < GifFile->SHeight; i++) {
                            GifRow = ScreenBuffer[GifFile->SHeight-i-1];
                            for (j = 0 ; j < GifFile->SWidth; j++) {
                                ColorMapEntry = &ColorMap->Colors[GifRow[j]];
                                Buffer[i*GifFile->SWidth*4+j*4] = ColorMapEntry->Red;
                                Buffer[i*GifFile->SWidth*4+j*4+1] = ColorMapEntry->Green;
                                Buffer[i*GifFile->SWidth*4+j*4+2] = ColorMapEntry->Blue;
                                if(GifRow[j] == GCB.TransparentColor) Buffer[i*GifFile->SWidth*4+j*4+3] = 0;
                                else Buffer[i*GifFile->SWidth*4+j*4+3] = 255;
                            }
                        }
                    }else{
                        Buffer = new unsigned char[GifFile->SHeight*GifFile->SWidth*3];
                        for (i = 0; i < GifFile->SHeight; i++) {
                            GifRow = ScreenBuffer[GifFile->SHeight-i-1];
                            for (j = 0 ; j < GifFile->SWidth; j++) {
                                if(GifRow[j] == GCB.TransparentColor && Blend){
                                    Buffer[i*GifFile->SWidth*3+j*3] = Imgs[Imgs.size()-1][i*GifFile->SWidth*3+j*3] ;
                                    Buffer[i*GifFile->SWidth*3+j*3+1] = Imgs[Imgs.size()-1][i*GifFile->SWidth*3+j*3+1];
                                    Buffer[i*GifFile->SWidth*3+j*3+2] = Imgs[Imgs.size()-1][i*GifFile->SWidth*3+j*3+2];
                                }else{
                                    ColorMapEntry = &ColorMap->Colors[GifRow[j]];
                                    Buffer[i*GifFile->SWidth*3+j*3] = ColorMapEntry->Red;
                                    Buffer[i*GifFile->SWidth*3+j*3+1] = ColorMapEntry->Green;
                                    Buffer[i*GifFile->SWidth*3+j*3+2] = ColorMapEntry->Blue;
                                }
                            }
                        }
                    }

                    Times.push_back(GCB.DelayTime);
                    Imgs.push_back(Buffer);
                    break;
                case EXTENSION_RECORD_TYPE:
            /* Skip any extension blocks in file: */
                    if (DGifGetExtension(GifFile, &ExtCode, &Extension) == GIF_ERROR) {
                        return GifFile->Error;
                    }
                    DGifExtensionToGCB(Extension[0],Extension+1,&GCB);
                    while (Extension != NULL) {
                        if (DGifGetExtensionNext(GifFile, &Extension) == GIF_ERROR) {
                            return GifFile->Error;
                        }
                    }
                    break;
                case TERMINATE_RECORD_TYPE:
                    break;
                default:		    /* Should be trapped by DGifGetRecordType. */
                    break;
            }
        } while (RecordType != TERMINATE_RECORD_TYPE);


        /* Lets dump it - set the global variables required and do it: */
        imgCount = Imgs.size();

        pixels = new unsigned char *[imgCount];

        if(imgCount>1)timeFotogram = new unsigned int [imgCount];
        else timeFotogram = 0;
        for(i = 0; i < imgCount; i++){
            if(imgCount>1)timeFotogram[i] = Times[i];
            pixels[i] = Imgs[i];
        }

        Imgs.clear();
        Times.clear();
        (void)free(ScreenBuffer);

        if (DGifCloseFile(GifFile) == GIF_ERROR) {
            return GifFile->Error;
        }
        return 0;
    }
}
