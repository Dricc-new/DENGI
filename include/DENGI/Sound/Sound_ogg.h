#ifndef DENGI_SOUND_OGG_H
#define DENGI_SOUND_OGG_H

#include "Sound.h"
#include "../kernel.h"

namespace dengi{
    class SoundOGG : public Sound{
        public:
            SoundOGG(){buffer = 0;};
            DENGIDEF ~SoundOGG();
            int DENGIDEF LoadFromFile(char* src);
                        unsigned int buffer;
        private:


    };
}

#endif
