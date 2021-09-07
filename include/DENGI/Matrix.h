#ifndef DENGI_MATRIX_H
#define DENGI_MATRIX_H

#include "kernel.h"

namespace dengi{
    class Matrix{
        public:
            DENGIDEF Matrix();
            float* DENGIDEF operator*(float *m);
            void DENGIDEF operator=(float *m);
            void DENGIDEF operator*=(float *m);
            void DENGIDEF translate(float x, float y, float z);
            void DENGIDEF rotate(float angle,float x, float y, float z);
            float* DENGIDEF get();
        private:
            float M[16];
    };
}
#endif
