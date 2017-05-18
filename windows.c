#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void win32_clear_screen(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0,0};       /* here's where we'll home the
                                        cursor */
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */

    /* get the number of character cells in the current buffer */
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */
    FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten);

    /* get the current text attribute */
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    /* now set the buffer's attributes accordingly */
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

    /* put the cursor at (0, 0) */
    SetConsoleCursorPosition(hConsole, coordScreen);
}
#endif