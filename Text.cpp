#include "../include/DENGI/Text.h"
#include "../include/DENGI/dengi.h"

namespace dengi{

    DENGIDEF Text::Text(Font *style){
        LengthText = 0;
        Mpos[0]  = 1.0;Mpos[1]  = 0.0;Mpos[2]  = 0.0;Mpos[3]  = 0.0;
        Mpos[4]  = 0.0;Mpos[5]  = 1.0;Mpos[6]  = 0.0;Mpos[7]  = 0.0;
        Mpos[8]  = 0.0;Mpos[9]  = 0.0;Mpos[10] = 1.0;Mpos[11] = 0.0;
        Mpos[12] = 0.0;Mpos[13] = 0.0;Mpos[14] = 0.0;Mpos[15] = 1.0;

        glGenVertexArrays(1,&Id);
        glGenBuffers(2,Buff);
        Style = style;
    }

    void DENGIDEF Text::SetFont(Font *style){
        Style = style;
        if(LengthText)Renderer();
    }

    void DENGIDEF Text::SetIndexs(char *s){
        unsigned int j;

        if(LengthText){
            delete ListChar;
            LengthText = 0;
        }

        while(s[LengthText]){
            LengthText++;
        }
        if(LengthText){

            ListChar = new NodeFont*[LengthText];

            for( j = 0; j < LengthText; j++ ){
                ListChar[j] = Style->SelectIndex((unsigned int)s[j]);
            }
            Renderer();
        }
    }

    void DENGIDEF Text::SetIndexs(unsigned int *s){
        unsigned int j;

        if(LengthText){
            delete ListChar;
            LengthText = 0;
        }

        while(s[LengthText]){
            LengthText++;
        }
        if(LengthText){

            ListChar = new NodeFont*[LengthText];

            for( j = 0; j < LengthText; j++ ){
                ListChar[j] = Style->SelectIndex(s[j]);
            }
            Renderer();
        }
    }

    void DENGIDEF Text::SetPos(int x,int y){
        Mpos[12] = (float)x;
        Mpos[13] = (float)y;
    }

    void DENGIDEF Text::GetSizeMetrics(float d[2]){
        d[0] = MetricX;
        d[1] = MetricY;
    }

    void DENGIDEF Text::Draw(){
        glBindVertexArray(Id);
        UseModelMatrix(Mpos);
        Filling->Draw();
        SetTypeObjectLocation(2);

        for( unsigned int i = 0; i < LengthText;i++){
            glBindTexture(GL_TEXTURE_2D, ListChar[i]->Texture);
            SetTextureDiffuseLocation();
            glDrawArrays(GL_QUADS,i*4,4);
        }
    }

    void DENGIDEF Text::DrawNF(){
        glBindVertexArray(Id);
        UseModelMatrix(Mpos);
        SetTypeObjectLocation(2);

        for( unsigned int i = 0; i < LengthText;i++){
            glBindTexture(GL_TEXTURE_2D, ListChar[i]->Texture);
            SetTextureDiffuseLocation();
            glDrawArrays(GL_QUADS,i*4,4);
        }
    }

    void DENGIDEF Text::Renderer(){

        glBindVertexArray(Id);

        GLint vert[8*LengthText];
        GLint uvs[8*LengthText];
        int advance = 0;
        vert[0] = 0;
        MetricY = 0;
        for( unsigned int i = 0; i < LengthText; i++){
            vert[i*8] = advance+ListChar[i]->BearingX;
            vert[i*8+1] = ListChar[i]->BearingY - ListChar[i]->Height;
            vert[i*8+2] = vert[i*8];
            vert[i*8+3] = ListChar[i]->BearingY;
            vert[i*8+4] = vert[i*8]+ListChar[i]->Width;
            vert[i*8+5] = vert[i*8+3];
            vert[i*8+6] = vert[i*8+4];
            vert[i*8+7] = vert[i*8+1];
            advance += ListChar[i]->Advance;
            if(MetricY < ListChar[i]->Height) MetricY = ListChar[i]->Height;
            uvs[i*8] = 0;
            uvs[i*8+1] = 1;
            uvs[i*8+2] = 0;
            uvs[i*8+3] = 0;
            uvs[i*8+4] = 1;
            uvs[i*8+5] = 0;
            uvs[i*8+6] = 1;
            uvs[i*8+7] = 1;

        }
        MetricX = advance - ListChar[LengthText-1]->Advance+ListChar[LengthText-1]->Width;

        glBindBuffer(GL_ARRAY_BUFFER,Buff[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLint)*8*LengthText,vert, GL_STATIC_DRAW);
        SetVertexsAttribLocation(2, GL_INT);

        glBindBuffer(GL_ARRAY_BUFFER,Buff[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLint)*8*LengthText,uvs, GL_STATIC_DRAW);
        SetUVsAttribLocation(2,GL_INT);

    }
}
