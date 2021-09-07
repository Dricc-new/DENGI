#include <string>
#include <vector>
#include "Matrix.h"
#include "Material.h"
#include "kernel.h"
using namespace std;
#ifndef DENGI_MODELWAVEFRONT_H
#define DENGI_MODELWAVEFRONT_H

namespace dengi{
    class WaveFront{
        public:
            DENGIDEF WaveFront();
            int DENGIDEF LoadFromFile(char* src);
            void DENGIDEF SetPos(float x, float y, float z);
            void DENGIDEF SetScale(float x, float y, float z);
            void DENGIDEF Draw();
        private:
            unsigned int Id;
            unsigned int imgId;
            unsigned int Buff[3];
            string srcMat;
            Matrix Mposs;
            float Mpos[16];
            vector<int> typeFace;
            vector<int> numcoord;
            vector<Material> materials;
            vector<unsigned int> mateInds;
    };
}
#endif // PICTURE_H

