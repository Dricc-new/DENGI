#include "../include/DENGI/dengi.h"
#include "../include/DENGI/Color.h"

namespace dengi{
    DENGIDEF Color::Color(float r,float g, float b, float a){
         color[0] = r;
         color[1] = g;
         color[2] = b;
         color[3] = a;
    }

    DENGIDEF Color::Color(float *c){
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        color[3] = c[3];
    }

    void DENGIDEF Color::SetColor(float r,float g, float b, float a){
         color[0] = r;
         color[1] = g;
         color[2] = b;
         color[3] = a;
    }

    void DENGIDEF Color::SetColor(float *c){
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        color[3] = c[3];
    }

    void DENGIDEF Color::Draw(){
        SetGradientColor1(color);
        SetGradientType();
    }
}
