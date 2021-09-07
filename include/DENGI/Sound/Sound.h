#ifndef DENGI_SOUND_H
#define DENGI_SOUND_H

namespace dengi{
    class Sound{
        public:
            virtual int LoadFromFile(char* src) = 0;
    };
}

#endif
