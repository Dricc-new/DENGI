#ifndef DENGI_TEXT_H
#define DENGI_TEXT_H

#include "kernel.h"

#include "Font.h"
#include <ft2build.h>
#include <freetype/freetype.h>
//#include "IDDList.h"

namespace dengi{
    class Text{
        public:
            DENGIDEF Text(Font *style);
            void DENGIDEF SetFont(Font *style);
            void DENGIDEF SetIndexs(char *s);
            void DENGIDEF SetIndexs(unsigned int *s);
            void DENGIDEF SetPos(int x,int y);
            void SetFilling(Fragment *filling){Filling = filling;};
            void DENGIDEF GetSizeMetrics(float d[2]);
            void DENGIDEF Draw();
            void DENGIDEF DrawNF();
        private:
            void DENGIDEF Renderer();
            float Mpos[16];
            unsigned int Id;
            unsigned int Buff[2];
            Fragment *Filling;
            unsigned int LengthText;
            NodeFont **ListChar;
            Font *Style;
            int MetricX, MetricY;
    };
}

#endif

