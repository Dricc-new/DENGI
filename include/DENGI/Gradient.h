#ifndef DENGI_GRADIENT_H
#define DENGI_GRADIENT_H

#include "Fragment.h"
#include "kernel.h"

namespace dengi{

    class Gradient : public Fragment{
        public:
            virtual void SetColor(float color1[4], float color2[4]) = 0;
            virtual void Draw() = 0;
    };

    class GradientLineal : public Gradient{
        public:
            DENGIDEF GradientLineal();
            void DENGIDEF SetColor(float color1[4], float color2[4]);
            void DENGIDEF SetAngle(double angle);
            void DENGIDEF SetScale(float scale);
            void DENGIDEF SetSize(float x, float y);
            void DENGIDEF SetSize(float d[2]);
            void DENGIDEF Draw();
        private:
            float Color[4];
            float Diff[4];
            float Transf[4];
            float Size[2];
    };

    class GradientRadial : public Gradient{
        public:
            DENGIDEF  GradientRadial();
            void DENGIDEF SetColor(float color1[4], float color2[4]);
            void DENGIDEF SetRadio(float r);
            void DENGIDEF SetSize(float x, float y);
            void DENGIDEF SetSize(float d[2]);
            void DENGIDEF Draw();
        private:
            float Color[4];
            float Diff[4];
            float Transf[4];
            float Size[2];
    };

    class GradientReflexive : public Gradient{
        public:
            DENGIDEF GradientReflexive();
            void DENGIDEF SetColor(float color1[4], float color2[4]);
            void DENGIDEF SetAngle(double angle);
            void DENGIDEF SetScale(float scale);
            void DENGIDEF SetSize(float x, float y);
            void DENGIDEF SetSize(float d[2]);
            void DENGIDEF Draw();
        private:
            float Color[4];
            float Diff[4];
            float Transf[4];
            float Size[2];
    };
}

#endif
