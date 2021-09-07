#include "../include/DENGI/dengi.h"
#include "../include/DENGI/Gradient.h"
#include <math.h>

namespace dengi{
    DENGIDEF GradientLineal::GradientLineal(){
        Color[0] = 0.0;
        Color[1] = 0.0;
        Color[2] = 0.0;
        Color[3] = 1.0;
        Diff[0] = 1.0;
        Diff[1] = 1.0;
        Diff[2] = 1.0;
        Diff[3] = 0.0;
        Transf[0] = 0.0;
        Transf[1] = 1.0;
        Transf[2] = 1.0;
        Transf[3] = 0.0;
        Size[0] = 100.0;
        Size[1] = 100.0;
    }

    void DENGIDEF GradientLineal::SetColor(float color1[4], float color2[4]){
        Color[0] = color1[0];
        Color[1] = color1[1];
        Color[2] = color1[2];
        Color[3] = color1[3];
        Diff[0] = color2[0] - color1[0];
        Diff[1] = color2[1] - color1[1];
        Diff[2] = color2[2] - color1[2];
        Diff[3] = color2[3] - color1[3];
    }

    void DENGIDEF GradientLineal::SetAngle(double angle){
        double Sin = sin(angle);
        Transf[0] = (float)(Sin*Sin);
        if(Sin>0.0)Transf[1] = 1.0;
        else Transf[1] = -1.0;
        if(cos(angle)>0.0) Transf[2] = 1.0;
        else Transf[2] = -1.0;
    }

    void DENGIDEF GradientLineal::SetScale(float scale){
        Transf[3] = scale;
    }

    void DENGIDEF GradientLineal::SetSize(float x, float y){
        Size[0] = x;
        Size[1] = y;
    }

    void DENGIDEF GradientLineal::SetSize(float d[2]){
        Size[0] = d[0];
        Size[1] = d[1];
    }

    void DENGIDEF GradientLineal::Draw(){
        SetGradientColor1(Color);
        SetGradientDifference(Diff);
        SetGradientTransformation(Transf);
        SetGradientType(1);
        SetGradientSize(Size);
    }

    DENGIDEF GradientRadial::GradientRadial(){
        Color[0] = 0.0;
        Color[1] = 0.0;
        Color[2] = 0.0;
        Color[3] = 1.0;
        Diff[0] = 1.0;
        Diff[1] = 1.0;
        Diff[2] = 1.0;
        Diff[3] = 0.0;
        Transf[0] = 0.0;
        Transf[1] = 0.0;
        Transf[2] = 0.0;
        Transf[3] = 10.0;
        Size[0] = 100.0;
        Size[1] = 100.0;
    }

    void DENGIDEF GradientRadial::SetColor(float color1[4], float color2[4]){
        Color[0] = color1[0];
        Color[1] = color1[1];
        Color[2] = color1[2];
        Color[3] = color1[3];
        Diff[0] = color2[0] - color1[0];
        Diff[1] = color2[1] - color1[1];
        Diff[2] = color2[2] - color1[2];
        Diff[3] = color2[3] - color1[3];
    }

    void DENGIDEF GradientRadial::SetRadio(float r){
        Transf[3] = r;
    }

    void DENGIDEF GradientRadial::SetSize(float x, float y){
        Size[0] = x/2;
        Size[1] = y/2;
    }

    void DENGIDEF GradientRadial::SetSize(float d[2]){
        Size[0] = d[0]/2;
        Size[1] = d[1]/2;
    }

    void DENGIDEF GradientRadial::Draw(){
        SetGradientColor1(Color);
        SetGradientDifference(Diff);
        SetGradientTransformation(Transf);
        SetGradientType(2);
        SetGradientSize(Size);
    }

    DENGIDEF GradientReflexive::GradientReflexive(){
        Color[0] = 0.0;
        Color[1] = 0.0;
        Color[2] = 0.0;
        Color[3] = 1.0;
        Diff[0] = 1.0;
        Diff[1] = 1.0;
        Diff[2] = 1.0;
        Diff[3] = 0.0;
        Transf[0] = 0.0;
        Transf[1] = 1.0;
        Transf[2] = 1.0;
        Transf[3] = 36.0;
        Size[0] = 100.0;
        Size[1] = 100.0;
    }

    void DENGIDEF GradientReflexive::SetColor(float color1[4], float color2[4]){
        Color[0] = color1[0];
        Color[1] = color1[1];
        Color[2] = color1[2];
        Color[3] = color1[3];
        Diff[0] = color2[0] - color1[0];
        Diff[1] = color2[1] - color1[1];
        Diff[2] = color2[2] - color1[2];
        Diff[3] = color2[3] - color1[3];
    }

    void DENGIDEF GradientReflexive::SetAngle(double angle){
        double Sin = sin(angle);
        Transf[0] = (float)(Sin*Sin);
        if(Sin>0.0)Transf[1] = 1.0;
        else Transf[1] = -1.0;
        if(cos(angle)>0.0) Transf[2] = 1.0;
        else Transf[2] = -1.0;
    }

    void DENGIDEF GradientReflexive::SetScale(float scale){
        Transf[3] = scale;
    }

    void DENGIDEF GradientReflexive::SetSize(float x, float y){
        Size[0] = x/2;
        Size[1] = y/2;
    }

    void DENGIDEF GradientReflexive::SetSize(float d[2]){
        Size[0] = d[0]/2;
        Size[1] = d[1]/2;
    }

    void DENGIDEF GradientReflexive::Draw(){
        SetGradientColor1(Color);
        SetGradientDifference(Diff);
        SetGradientTransformation(Transf);
        SetGradientType(3);
        SetGradientSize(Size);
    }

}
