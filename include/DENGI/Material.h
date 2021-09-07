#ifndef MATERIAL_H
#define MATERIAL_H

#include "kernel.h"

namespace dengi{

    class Material
    {
        public:
            Material();
            void DENGIDEF SetKa( float r, float g, float b);
            void DENGIDEF SetKd( float r, float g, float b);
            void DENGIDEF SetKs( float r, float g, float b);
            void DENGIDEF SetNs( float Ns);
            void DENGIDEF SetMap_Kd(char* src);
            void DENGIDEF SetAlpha( float alpha);
            void DENGIDEF Use();
        private:
            float Ka[3];
            float Kd[3];
            float Ks[3];
            float Ns;
            unsigned int Map_Kd;
            float alpha;
    };
}
#endif // MATERIAL_H
