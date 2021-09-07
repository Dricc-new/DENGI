#ifndef DENGI_BACKGROUND_H
#define DENGI_BACKGROUND_H

namespace dengi{
    class Background{
        public:
            Background();
            void LoadImage();
            void SetPos(float x, float y);
            void Draw();
        private:

    };
}

#endif
