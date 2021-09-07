#include "../include/DENGI/dengi.h"
#include "../include/DENGI/Color.h"
#include <math.h>
#include <al.h>
#include <alc.h>

namespace dengi{
    sf::RenderWindow *Window;
    unsigned int Program;

    unsigned int VertexsAttribLocation;
    unsigned int ColorsAttribLocation;
    unsigned int NormalsAttribLocation;
    unsigned int UVsAttribLocation;

    unsigned int P_MatrixLocation;
    unsigned int V_MatrixLocation;
    unsigned int M_MatrixLocation;
    unsigned int TypeObjectLocation;

    unsigned int GradientTypeLocation;
    unsigned int GradientColor1Location;
    unsigned int GradientDiffLocation;
    unsigned int GradientTansformLocation;
    unsigned int GradientSizeLocation;

    unsigned int MaterialKaLocation;
    unsigned int MaterialKdLocation;
    unsigned int MaterialKsLocation;
    unsigned int MaterialNsLocation;
    unsigned int MaterialalphaLocation;

    unsigned int ModeLocation;
    unsigned int TextureDiffuseLocation;
    //unsigned int DisplacementMappingLocation;

    float *Matrix2D = 0;
    float Cam2D[16] = { 1.0,0.0,0.0,0.0,
                        0.0,1.0,0.0,0.0,
                        0.0,0.0,1.0,0.0,
                        0.0,0.0,0.0,1.0};
    float *Matrix3D = 0;



    int DENGIDEF DengiInit(sf::RenderWindow *win){
        win->setActive(true);
        Window = win;
        GLenum err = glewInit();

        if (GLEW_OK != err)
        {
            return -1;
        }

        glViewport(0,0,800,600);
        glClearColor(0.1, 1.1, 0.1, 1.0);
        glEnable(GL_BLEND);
        glBlendFunc( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER,0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    glOrtho(0,1024,0,768,-1,1);
        glShadeModel(GL_SMOOTH);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return 0;
    }

    void DENGIDEF ActiveMode(unsigned int mode){
        float SizeX, SizeY;
        SizeX = Window->getSize().x;
        SizeY = Window->getSize().y;
        if(mode&DENGI_MODE2D){
            Matrix2D = new float[16];
            Matrix2D[0] = 2.0/SizeX;    Matrix2D[1] = 0.0;          Matrix2D[2] = 0.0;  Matrix2D[3] = 0.0;
            Matrix2D[4] = 0.0;          Matrix2D[5] = 2.0/SizeY;    Matrix2D[6] = 0.0;  Matrix2D[7] = 0.0;
            Matrix2D[8] = 0.0;          Matrix2D[9] = 0.0;          Matrix2D[10]=-2.0;  Matrix2D[11]= 0.0;
            Matrix2D[12] = -1;         Matrix2D[13]= -1;          Matrix2D[14] = 0.0; Matrix2D[15] = 1.0;
        }
        if(mode&DENGI_MODE3D){
            glDepthFunc(GL_LEQUAL);
            glDepthRange(-1,1);

            float ar = SizeY/SizeX;
            float zNear = 1.f;
            float zFar = 1000.f;
            float zRange = zNear-zFar;
            float h_div = tan((40*3.14)/360);
            float w_div = ar*h_div;
            Matrix3D = new float[16];
            Matrix3D[0] = 1.0/h_div;    Matrix3D[1] = 0.0;          Matrix3D[2] = 0.0;                  Matrix3D[3] = 0.0;
            Matrix3D[4] = 0.0;          Matrix3D[5] = 1.0/w_div;    Matrix3D[6] = 0.0;                  Matrix3D[7] = 0.0;
            Matrix3D[8] = 0.0;          Matrix3D[9] = 0.0;          Matrix3D[10]=(zFar-zNear)/zRange;   Matrix3D[11]= 2.0*zFar*zNear/zRange;
            Matrix3D[12] = 0.0;         Matrix3D[13]= 0.0;          Matrix3D[14] = 0.0;                 Matrix3D[15] = 1.0;
        }
    }

    void DENGIDEF Mode2D(){
        UseViewMatrix(Cam2D);
        glUniform1ui(ModeLocation, 1);
        glDisable(GL_DEPTH_TEST);
        UsePojectionMatrix(Matrix2D);
    }

    void DENGIDEF Mode3D(){
        glUniform1ui(ModeLocation, 2);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        UsePojectionMatrix(Matrix3D);
    }

    char *LoadFromFile(char *src){
        FILE *FileCode = fopen(src,"r");
        if(!FileCode){
            return 0;
        }

        unsigned long long int LengthFile = 0;
        while( getc(FileCode) != EOF ){
            LengthFile++;
        }

        rewind(FileCode);
        char *Code = new char[LengthFile+1] ;
        Code[LengthFile] = (char)NULL;
        for(unsigned long long int i = 0; i < LengthFile; i++){
            Code[i] = getc(FileCode);
        }
        fclose(FileCode);
        return Code;
    }

    void DENGIDEF PrintERROR(GLuint obj){
        GLint Error;
        glGetShaderiv(obj, GL_COMPILE_STATUS, &Error );
        if(!Error){
            GLint length;
            GLchar* log;
            glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&length );
            log = (GLchar*) malloc(length);
            glGetShaderInfoLog(obj, length, &length, log);
            fprintf(stderr,"compile log = %s\n", log);
            free(log);
        }
    }

    void DENGIDEF UsePojectionMatrix(float *matrix){
        glUniformMatrix4fv(P_MatrixLocation,1,0,matrix);
    }

    void DENGIDEF UseViewMatrix(float *matrix){
        glUniformMatrix4fv(V_MatrixLocation,1,0,matrix);
    }

    void DENGIDEF UseModelMatrix(float *matrix){
        glUniformMatrix4fv(M_MatrixLocation,1,0,matrix);
    }

    void DENGIDEF SetVertexsAttribLocation(int Size, GLenum Type){
        glVertexAttribPointer(VertexsAttribLocation,Size,Type,0,0,0);
        glEnableVertexAttribArray(VertexsAttribLocation);
    }

    void DENGIDEF SetColorsAttribLocation(int Size, GLenum Type){
        glVertexAttribPointer(ColorsAttribLocation,Size,Type,0,0,0);
        glEnableVertexAttribArray(ColorsAttribLocation);
    }

    void DENGIDEF SetNormalsAttribLocation(int Size, GLenum Type){
        glVertexAttribPointer(NormalsAttribLocation,Size,Type,0,0,0);
        glEnableVertexAttribArray(NormalsAttribLocation);
    }

    void DENGIDEF SetUVsAttribLocation(int Size, GLenum Type){
        glVertexAttribPointer(UVsAttribLocation,Size,Type,0,0,0);
        glEnableVertexAttribArray(UVsAttribLocation);
    }

    void DENGIDEF SetTextureDiffuseLocation(){
        glUniform1i(TextureDiffuseLocation,0);
    }

    void DENGIDEF SetTypeObjectLocation(int Type){
        glUniform1ui(TypeObjectLocation,Type);
    }

    void DENGIDEF SetGradientType(int Type){
        glUniform1i(GradientTypeLocation, Type);
    }

    void DENGIDEF SetGradientColor1(float *color){
        glUniform4fv(GradientColor1Location,1,color);
    }

    void DENGIDEF SetGradientDifference(float *diff){
        glUniform4fv(GradientDiffLocation,1,diff);
    }

    void DENGIDEF SetGradientTransformation(float *Transform){
        glUniform4fv(GradientTansformLocation,1,Transform);
    }

    void DENGIDEF SetGradientSize(float *Size){
        glUniform2fv(GradientSizeLocation,1,Size);
    }

    void DENGIDEF SetMaterial(float *Ka, float *Kd, float *Ks, float Ns, float alpha){
        glUniform3fv(MaterialKaLocation,1,Ka);
        glUniform3fv(MaterialKdLocation,1,Kd);
        glUniform3fv(MaterialKsLocation,1,Ks);
        glUniform1f(MaterialNsLocation,Ns);
        glUniform1f(MaterialalphaLocation,alpha);
    }

    void DENGIDEF CompileProgram(){
        GLint compiled;
        const char *VSource = LoadFromFile((char*)"Shaders/VShader.c");
        const char *FSource = LoadFromFile((char*)"Shaders/FShader.c");

        GLuint VShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint FShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(VShader,1,&VSource,NULL);
        glShaderSource(FShader,1,&FSource,NULL);

        glCompileShader(VShader);
        glCompileShader(FShader);

        PrintERROR(VShader);
        PrintERROR(FShader);

        Program = glCreateProgram();

        glAttachShader(Program, VShader);
        glAttachShader(Program, FShader);
        glLinkProgram(Program);

        glGetProgramiv(Program, GL_LINK_STATUS, &compiled );
        printf("compiler FShader %d\n",compiled);

    }

    void DENGIDEF UseProgram(){
        glUseProgram(Program);

        VertexsAttribLocation = glGetAttribLocation(Program, "position");
        NormalsAttribLocation = glGetAttribLocation(Program, "normals");
        ColorsAttribLocation  = glGetAttribLocation(Program, "color");
        UVsAttribLocation     = glGetAttribLocation(Program, "uvs");

        P_MatrixLocation  = glGetUniformLocation(Program, "P_Matrx");
        V_MatrixLocation  = glGetUniformLocation(Program, "V_Matrx");
        M_MatrixLocation  = glGetUniformLocation(Program, "M_Matrx");

        TypeObjectLocation = glGetUniformLocation(Program, "type");
        ModeLocation = glGetUniformLocation(Program, "Mode");

        GradientTypeLocation = glGetUniformLocation(Program, "gradient.Type");
        GradientColor1Location = glGetUniformLocation(Program, "gradient.Color1");
        GradientDiffLocation = glGetUniformLocation(Program, "gradient.Diff");
        GradientTansformLocation = glGetUniformLocation(Program, "gradient.Transf");
        GradientSizeLocation = glGetUniformLocation(Program, "gradient.Size");

        MaterialKaLocation = glGetUniformLocation(Program, "material.Ka");
        MaterialKdLocation = glGetUniformLocation(Program, "material.Kd");
        MaterialKsLocation = glGetUniformLocation(Program, "material.Ks");
        MaterialNsLocation = glGetUniformLocation(Program, "material.Ns");
        MaterialalphaLocation = glGetUniformLocation(Program, "material.alpha");

    }
}

