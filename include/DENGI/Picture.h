#ifndef PICTURE_H
#define PICTURE_H

#include "kernel.h"

namespace dengi{
    class Picture{
        public:
            DENGIDEF Picture();
            int DENGIDEF LoadFromFile(char* src);
            void DENGIDEF SetPos(int x, int y);
            void DENGIDEF SetScale(float x, float y);
            void DENGIDEF Draw();
        private:
            unsigned int Id;
            unsigned int imgId;
            unsigned int Buff[2];

            float Mpos[16];
    };
}
#endif // PICTURE_H
