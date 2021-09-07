#ifndef DENGI_GLYFONODE_H
#define DENGI_GLYFONODE_H

namespace dengi{
    class GlyfoNode{
        public:
            int BearingX;
            int BearingY;
            int Advance;
            int Height;
            int Width;
            unsigned int Texture;
            unsigned int ind;
    };
}

#endif


