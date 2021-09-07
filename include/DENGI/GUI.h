#include "kernel.h"

#if defined(_WIN32)
    #include <windows.h>
#endif

#include "GUI/windows.h"

namespace dengi{
    int DENGIDEF LoadIconFromFile(Window *win,char *src);
    int DENGIDEF LoadIconFromImage(Window *win,char *src);
    int DENGIDEF LoadIconFromResource(Window *win,char id_resource);
}
