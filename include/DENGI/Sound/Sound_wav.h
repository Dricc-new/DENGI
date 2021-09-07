#ifndef DENGI_SOUND_WAV_H
#define DENGI_SOUND_WAV_H

#include "Sound.h"
#include "../kernel.h"

namespace dengi{
    class SoundWAV : public Sound{
        public:
            SoundWAV(){buffer = 0;};
            DENGIDEF ~SoundWAV();
            int DENGIDEF LoadFromFile(char* src);
                        unsigned int buffer;
        private:


    };
}

#endif
