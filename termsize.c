#ifdef unix  /* sys/ioctl.h only exists under unix */

#include <sys/ioctl.h>

int termsize(int x)
{
    struct winsize sz;

    ioctl(1,TIOCGWINSZ,&sz);
    
    switch(x) {
    case 'r': return sz.ws_row;
    case 'c': return sz.ws_col;
    default:  return -1;
    }
}

#elif defined(_WIN32) /* okay, let's do it the windows way */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int termsize(int x)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
    GetConsoleScreenBufferInfo(hConsole,&csbi);

    switch(x) {
    case 'r': return csbi.dwSize.Y;
    case 'c': return csbi.dwSize.X;
    default:  return -1;
    }
}

#else   /* nope */

#define termsize(...) 0

#endif