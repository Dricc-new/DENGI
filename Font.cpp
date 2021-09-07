#include "../include/DENGI/Font.h"
#include "../include/DENGI/dengi.h"

namespace dengi{

    DENGIDEF Font::Font(char *src){
        root = 0;
        if(!FT_Init_FreeType(&library)){
            if(!FT_New_Face( library, src, 0, &face)){
                FT_Set_Pixel_Sizes(face,0,20);
            }
        }
    }

    void DENGIDEF Font::SetFile(char *src){
        FT_New_Face( library, src, 0, &face);
        if(root)Render(root);
    }

    void DENGIDEF Font::SetIndexs(char s){
        SetIndexs((unsigned int)s);
    }

    void DENGIDEF Font::SetIndexs(unsigned int s){
        bool Sent = true;

        if(!root){
            root = new NodeFont;
            root->left = 0;
            root->right = 0;
            RenderGlyfo(root,s);
            Sent = false;
        }
        NodeFont *ptr = root;
        while(Sent){
            if(ptr->ind == s){
                Sent = false;
            }else if(ptr->ind > s){
                if(ptr->right){
                    ptr = ptr->right;
                }else{
                    ptr->right = new NodeFont;
                    ptr = ptr->right;
                    ptr->left = 0;
                    ptr->right = 0;
                    RenderGlyfo(ptr,s);
                    Sent = false;
                }
            }else{
                if(ptr->left){
                    ptr = ptr->left;
                }else{
                    ptr->left = new NodeFont;
                    ptr = ptr->left;
                    ptr->left = 0;
                    ptr->right = 0;
                    RenderGlyfo(ptr,s);
                    Sent = false;
                }
            }
        }
    }

    void DENGIDEF Font::SetSize(unsigned int Size){
        FT_Set_Pixel_Sizes(face,0,Size);
        if(root)Render(root);
    }

    NodeFont* DENGIDEF Font::SelectIndex(unsigned int ind){

        if(!root){
            root = new NodeFont;
            root->left = 0;
            root->right = 0;
            RenderGlyfo(root,ind);
            return root;
        }
        Ptr = root;
        while(true){
            if(Ptr->ind == ind){
                return Ptr;
            }else if(Ptr->ind > ind){
                if(Ptr->right){
                    Ptr = Ptr->right;
                }else{
                    Ptr->right = new NodeFont;
                    Ptr = Ptr->right;
                    Ptr->left = 0;
                    Ptr->right = 0;
                    RenderGlyfo(Ptr,ind);
                    return Ptr;
                }
            }else{
                if(Ptr->left){
                    Ptr = Ptr->left;
                }else{
                    Ptr->left = new NodeFont;
                    Ptr = Ptr->left;
                    Ptr->left = 0;
                    Ptr->right = 0;
                    RenderGlyfo(Ptr,ind);
                    return Ptr;
                }
            }
        }
    }

    void DENGIDEF  Font::RenderGlyfo(NodeFont *ptr, unsigned int ind){
        FT_Load_Glyph(face,FT_Get_Char_Index(face,ind),FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL );
        ptr->ind = ind;
        ptr->Width = face->glyph->bitmap.width;
        ptr->Height = face->glyph->bitmap.rows;
        ptr->BearingX = face->glyph->metrics.horiBearingX/64;
        ptr->BearingY = face->glyph->metrics.horiBearingY/64;
        ptr->Advance =  face->glyph->metrics.horiAdvance/64;
        glGenTextures(1,&ptr->Texture);
        glBindTexture(GL_TEXTURE_2D, ptr->Texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
    }

    void DENGIDEF  Font::Render(NodeFont *ptr){
        if(ptr->left){
            Render(ptr->left);
        }

        if(ptr->right){
            Render(ptr->right);
        }

        FT_Load_Glyph(face,FT_Get_Char_Index(face,ptr->ind),FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL );
        ptr->Width = face->glyph->bitmap.width;
        ptr->Height = face->glyph->bitmap.rows;
        ptr->BearingX = face->glyph->metrics.horiBearingX/64;
        ptr->BearingY = face->glyph->metrics.horiBearingY/64;
        ptr->Advance =  face->glyph->metrics.horiAdvance/64;
        glBindTexture(GL_TEXTURE_2D, ptr->Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
    }
}
