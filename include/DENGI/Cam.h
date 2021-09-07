#ifndef DENGI_CAM_H
#define DENGI_CAM_H
#include "Matrix.h"

#include "kernel.h"

namespace dengi{
    class Cam{
        public:
            DENGIDEF Cam();
            void DENGIDEF SetPos(float x, float y, float z);
            void DENGIDEF Use();
        private:
            float R[16];
            float T[16];
            Matrix LookAt;
    };
}

#endif
