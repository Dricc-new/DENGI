#ifndef DENGI_FONT_H
#define DENGI_FONT_H

#include "kernel.h"

#include "GlyfoN.h"
#include "Fragment.h"
#include <ft2build.h>
#include <freetype/freetype.h>

namespace dengi{
    struct NodeFont{
            int BearingX;
            int BearingY;
            int Advance;
            int Height;
            int Width;
            unsigned int Texture;
            unsigned int ind;
            NodeFont *left, *right;
    };

    class Font{
        public:
            DENGIDEF Font(char *src);

            void DENGIDEF SetFile(char *src);
            void DENGIDEF SetIndexs(char s);
            void DENGIDEF SetIndexs(unsigned int s);
            void DENGIDEF SetSize(unsigned int Size);
            NodeFont* DENGIDEF SelectIndex(unsigned int ind);
        private:
            FT_Library library;
            FT_Face face;
            Fragment *Filling;
            unsigned int LengthListGlyfo;
            NodeFont *root;
            NodeFont *Ptr;
            void DENGIDEF RenderGlyfo(NodeFont *ptr, unsigned int ind);
            void DENGIDEF Render(NodeFont *ptr);
    };
}

#endif
