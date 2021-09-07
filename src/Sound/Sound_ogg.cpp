#include "../../include/DENGI/Sound/Sound_ogg.h"
#include "../../include/DENGI/dengi.h"
#include <al.h>
#include <alc.h>
#include <ogg/ogg.h>
namespace dengi{
    DENGIDEF SoundOGG::~SoundOGG(){

    }

    int DENGIDEF SoundOGG::LoadFromFile(char* src){
        FILE *file = fopen(src,"rb");
        if(!file){
            return -1;
        }

        ogg_sync_state state;
        int ret = ogg_sync_init(&state);

        ogg_page page;
        while(ogg_sync_pageout(&state,&page)!=1){
            char *buffer = ogg_sync_buffer(&state,4096);

        }
        /*unsigned int header[3];
        fread(header,4,3,file);
        if(header[0] != 0x46464952 || header[2] != 0x45564157){
            fclose(file);
            return 1;
        }
        unsigned int Subchunk1[3];
        fread(Subchunk1,4,3,file);
        if((Subchunk1[2]&0x0000ffff) == 1){
            unsigned int Format[3];
            fread(Format,4,3,file);
            printf("NumChannel      :%d \n", Subchunk1[1]);
            printf("SampleRate      :%d \n", Format[0]);
            printf("ByteRate        :%d \n", Format[1]);
            printf("BlockAlign      :%d \n", Format[2]&0x0000ffff);
            printf("BitsPerSample   :%d \n", Format[2]>>16);
            int Subchunk2[2];

            fread(Subchunk2,4,2,file);
            printf("is data: __0x%x__\n",Subchunk2[0]);
            printf("is data: __%d__\n",Subchunk2[1]);
            unsigned char *data = new unsigned char[Subchunk2[1]];
            fread(data,1,Subchunk2[1],file);
            alGenBuffers(1, &buffer);
            alBufferData(buffer, AL_FORMAT_MONO16, data, Subchunk2[1], Format[0]);
            delete data;
        }*/
        fclose(file);
        return 0;
    }
}
