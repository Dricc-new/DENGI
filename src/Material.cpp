#include "../include/DENGI/Material.h"
#include "../include/DENGI/dengi.h"
#include "../include/DENGI/Image.h"
#include "../include/DENGI/Img/Img_png.h"

namespace dengi{
    DENGIDEF Material::Material()
    {
        Ka[0] = 0.5; Ka[1] = 0.5; Ka[2] = 0.5;
        Kd[0] = 0.5; Kd[1] = 0.5; Kd[2] = 0.5;
        Ks[0] = 1.0; Ks[1] = 1.0; Ks[2] = 1.0;
        Ns = 0;
        alpha = 1.0;
        Map_Kd = 0;
    }

    void DENGIDEF Material::SetKa( float r, float g, float b){
        Ka[0] = r; Ka[1] = g; Ka[2] = b;
    }

    void DENGIDEF Material::SetKd( float r, float g, float b){
            Kd[0] = r; Kd[1] = g; Kd[2] = b;
    }

    void DENGIDEF Material::SetKs( float r, float g, float b){
            Ks[0] = r; Ks[1] = g; Ks[2] = b;
    }

    void DENGIDEF Material::SetNs( float ns){
        Ns = ns;
    }

    void DENGIDEF Material::SetMap_Kd( char* src){
        ImgPNG img;
        if(img.LoadFromFile(src)){

        }

        glGenTextures(1, &Map_Kd);
        glBindTexture(GL_TEXTURE_2D, Map_Kd);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, img.GetFormat(), img.GetWidth(), img.GetHeight(), 0, img.GetFormat(), img.GetDistrData(), img.GetBuffer());
    }

    void DENGIDEF Material::SetAlpha( float A){
        alpha = A;
    }

    void DENGIDEF Material::Use(){
        SetMaterial(Ka, Kd, Ks, Ns, alpha);
        glBindTexture(GL_TEXTURE_2D, Map_Kd);
        SetTextureDiffuseLocation();
    }
}
