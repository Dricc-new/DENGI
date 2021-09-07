#include "../include/DENGI/Picture.h"
#include "../include/DENGI/dengi.h"
#include "../include/DENGI/Image.h"

namespace dengi{

    DENGIDEF Picture::Picture(){
        glGenVertexArrays(1,&Id);
        glGenBuffers(2,Buff);

        Mpos[0]  = 1.0;Mpos[1]  = 0.0;Mpos[2]  = 0.0;Mpos[3]  = 0.0;
        Mpos[4]  = 0.0;Mpos[5]  = 1.0;Mpos[6]  = 0.0;Mpos[7]  = 0.0;
        Mpos[8]  = 0.0;Mpos[9]  = 0.0;Mpos[10] = 1.0;Mpos[11] = 0.0;
        Mpos[12] = 0.0;Mpos[13] = 0.0;Mpos[14] = 0.0;Mpos[15] = 1.0;
    }

    void DENGIDEF Picture::SetPos(int x, int y){
        Mpos[12] = (float)x;
        Mpos[13] = (float)y;
    }

    void DENGIDEF Picture::SetScale(float x, float y){
        Mpos[0] = x;
        Mpos[5] = y;
        Mpos[12] /= x;
        //Mpos[13] -= y;
    }

    int DENGIDEF Picture::LoadFromFile(char* src){
        Image *img = new Image;
        if(img->LoadFromFile(src)){
            delete img;
            return 1;
        }

        unsigned int width  = img->GetWidth();
        unsigned int height  = img->GetHeight();

        GLint vert[8] = { 0, 0, 0, (int)height, (int)width, (int)height, (int)width, 0};
        GLint texture[8] = {    0, 0,
                                0, 1,
                                1, 1,
                                1, 0};

        glBindVertexArray(Id);

        glBindBuffer(GL_ARRAY_BUFFER,Buff[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vert),vert, GL_STATIC_DRAW);
        SetVertexsAttribLocation(2 , GL_INT);

        glBindBuffer(GL_ARRAY_BUFFER,Buff[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texture),texture, GL_STATIC_DRAW);
        SetUVsAttribLocation(2 , GL_INT);

        glGenTextures(1, &imgId);
        glBindTexture(GL_TEXTURE_2D, imgId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->GetBuffer());
        delete img;
        return 0;
    }

    void DENGIDEF Picture::Draw(){
        UseModelMatrix(Mpos);
        glBindVertexArray(Id);
        glBindTexture(GL_TEXTURE_2D, imgId);
        SetTextureDiffuseLocation();
        SetTypeObjectLocation(1);
        glDrawArrays(GL_QUADS,0,4);
    }
}
