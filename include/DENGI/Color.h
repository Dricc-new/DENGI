#ifndef DENGI_COLOR_H
#define DENGI_COLOR_H

#include "kernel.h"
#include "Fragment.h"

namespace dengi{
    class DENGIDEF Color : public Fragment{
        public:
            Color(float r = 0, float g = 0, float b = 0, float a = 0);
            Color(float *c);
            void SetColor(float r = 0, float g = 0, float b = 0, float a = 0);
            void SetColor(float *c);
            void Draw();
        private:
            float color[4];
    };
}

#endif
