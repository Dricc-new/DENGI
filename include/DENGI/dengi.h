#define SFML_STATIC
#include <SFML/Graphics.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#include "Fragment.h"
#include <iostream>

#define DENGI_MODE2D 0x01
#define DENGI_MODE3D 0x02

#include "kernel.h"

namespace dengi{
    enum GradientType{None,Lineal,Radial,Reflexive};
    int DENGIDEF DengiInit(sf::RenderWindow *win);
    void DENGIDEF CompileProgram();

    void DENGIDEF ActiveMode(unsigned int mode);
    void DENGIDEF Mode2D();
    void Mode3D();

    void DENGIDEF UseProgram();
    void DENGIDEF UseModelMatrix(float *matrix);
    void DENGIDEF UsePojectionMatrix(float *matrix);
    void DENGIDEF UseViewMatrix(float *matrix);
    void DENGIDEF SetVertexsAttribLocation(int Size, GLenum type);
    void DENGIDEF SetColorsAttribLocation(int Size, GLenum type);
    void DENGIDEF SetUVsAttribLocation(int Size, GLenum type);
    void DENGIDEF SetNormalsAttribLocation(int Size, GLenum type);
    void DENGIDEF SetTextureDiffuseLocation();
    void DENGIDEF SetTypeObjectLocation(int Type=0);
    void DENGIDEF SetMaterial(float *Ka, float *Kd, float *Ks, float Ns, float alpha);

    void DENGIDEF SetGradientType(int Type=GradientType::None);
    void DENGIDEF SetGradientColor1(float *color);
    void DENGIDEF SetGradientDifference(float *diff);
    void DENGIDEF SetGradientTransformation(float *Transform);
    void DENGIDEF SetGradientSize(float *Size);
}
