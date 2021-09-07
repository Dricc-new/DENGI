#include <windows.h>
#include "include/DENGI/dengi.h"
#include "include/DENGI/Color.h"
#include "include/DENGI/Gradient.h"
#include "include/DENGI/Text.h"
#include "include/DENGI/Picture.h"
#include "include/DENGI/Cam.h"
#include "include/DENGI/Image.h"
#include "include/DENGI/ModelWavefront.h"
#include "include/DENGI/Img/Img_png.h"
#include "include/DENGI/Img/Img_jpeg.h"
#include "include/DENGI/Img/Img_gif.h"
#include "include/DENGI/Img/Img_bmp.h"
#include "include/DENGI/Sound/Sound_wav.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

#include <al.h>
#include <alc.h>
#define ANGLE 30

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}


using namespace sf;
int main()
{
    HINSTANCE hInstance;
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

int nCmdShow = 10;
    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = NULL;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;

//__MINGW_NAME_AW(1);

    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          600+48,
                          NULL,
                          NULL,
                          NULL,
                          NULL);

    ShowWindow(hwnd, nCmdShow);
    float theta = 0.0f;
    /* program main loop */
        /*EnableOpenGL(hwnd, &hDC, &hRC);
    while (!bQuit)
    {
        /* check for messages */
      /*  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
   /*         if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

     /*       glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
            glRotatef(theta, 0.0f, 0.0f, 1.0f);

            glBegin(GL_TRIANGLES);

                glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f,   1.0f);
                glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f,  -0.5f);
                glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);

            glEnd();

            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);
        }
    }


DestroyWindow(hwnd);*/


    ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    Clock clock;
    Clock clock2;

    RenderWindow window(VideoMode(800,600,32),"Dengi 1.0 beta!", sf::Style::Default, contextSettings);
           EnableOpenGL(hwnd, &hDC, &hRC);

    dengi::DengiInit(&window);

    dengi::CompileProgram();
    dengi::UseProgram();
    dengi::ActiveMode(DENGI_MODE2D|DENGI_MODE3D);
    printf("%s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("%s\n",glGetString(GL_VERSION));
    //dengi::Picture ggg;
    //ggg.LoadFromFile((char*)"back.png");
    //ggg.SetPos(1,1);
    dengi::ImgBMP background;
//    background.Blend = false;
    printf("%d",background.LoadFromFile((char*)"testimg.bmp"));




    ALCdevice *device;
    ALCcontext *context;

    device = alcOpenDevice(NULL);
    if (device){
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent (context);
    }else{
        return 0;
    }
    /*dengi::SoundWAV music;
    printf("Music loader: %d",music.LoadFromFile((char*)"music.wav"));

ALuint source;
alGenSources(1, &source);


ALfloat SourcePos[3] = {-15.0,0.0,0.0};
ALfloat SourceVel[3] = {0.0,0.0,0.0};
ALfloat ListenerPos[3] = {0.0,0.0,0.0};
ALfloat ListenerVel[3] = {0.0,0.0,0.0};
ALfloat ListenerOr[6] = {0.0,0.0,-1.0,0.0,1.0,0.0};


alSourcei(source, AL_BUFFER, music.buffer);
alSourcef(source, AL_PITCH, 2.0);
alSourcef(source, AL_GAIN, 1.0);
alSourcefv(source, AL_POSITION, SourcePos);
alSourcefv(source, AL_VELOCITY, SourceVel);
alSourcei(source, AL_LOOPING, 0);

alListenerfv(AL_POSITION, ListenerPos);
alListenerfv(AL_VELOCITY, ListenerVel);
alListenerfv(AL_ORIENTATION, ListenerOr);
alSourcePlay(source);

*/
    //dengi::GradientReflexive color1;
    dengi::Color color2(1.0,1.0,1.0,1.0);
    //color1.SetAngle(3.14/4);

    dengi::Font Style1((char*)"arial.ttf");
    Style1.SetSize(48);

    dengi::Font Style2((char*)"arial.ttf");
    Style2.SetSize(12);

    dengi::Text texto(&Style1);
    dengi::Text FPS(&Style2);

    texto.SetPos(0,0);
    texto.SetFilling(&color2);
    texto.SetIndexs((char *)"El motor soporta tanto 2D como 3D");

    FPS.SetPos(0,600-12);
    FPS.SetFilling(&color2);
    //float sixe[2];
    //texto.GetSizeMetrics(sixe);
    //color1.SetSize(sixe);
    //float c1[4] = {0.0,0.8823529412,0.9882352941,1.0},c2[4] = {0.0,0.4941176471,1.0,1.0};
    //color1.SetColor(c1,c2);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    Event event;
    dengi::Cam Camera1;
    Camera1.SetPos(0.0,0.5,0.5);

    //dengi::WaveFront Model3D;
    //Model3D.LoadFromFile("Modelos3D/eevee/eevee.obj");

    //dengi::WaveFront Rock;
    //Rock.LoadFromFile("Modelos3D/Rock/Rock.obj");

    unsigned int fotogram = 0;
    std::string fpstext;
    int fps = 0;

    while(window.isOpen()){
           // SourcePos[0]+=0.01;
/*alSourcefv(source, AL_POSITION, SourcePos);*/
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearDepth(1);
            glDepthFunc(GL_LEQUAL);

            dengi::Mode2D();
                glRasterPos2i(0,0);
                glDrawPixels(background.GetWidth() , background.GetHeight() , background.GetFormat() ,background.GetDistrData(), background.GetBuffer());

//                ggg.Draw();

            dengi::Mode3D();
                Camera1.Use();
                //Model3D.Draw();
                //Rock.Draw();
            dengi::Mode2D();

            texto.Draw();
            FPS.Draw();

            //glFlush();

            /*if(clock2.getElapsedTime().asMilliseconds()>background.GetTimeFotogram(fotogram)*10){
                fotogram++;
                clock2.restart();
            }*/
//            if(fotogram == background.GetNumImgs())fotogram = 0;
            if(clock.getElapsedTime().asMilliseconds()>999){
                clock.restart();
                fpstext = "FPS: ";
                fpstext+= std::to_string(fps);
                FPS.SetIndexs((char *)fpstext.c_str());
                fps=0;
            }
            fps++;
                        SwapBuffers(hDC);
            window.display();


    }
    glDisable(GL_TEXTURE_2D);
    //glBindBuffer(GL_ARRAY_BUFFER,0);
    window.setActive(true);
    return 0;
}
