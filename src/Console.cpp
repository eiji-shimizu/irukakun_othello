#include "Console.h"

#include <windows.h>

namespace IrukakunOthello
{
    void getCursorPosition(short &x, short &y)
    {
        HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hCons, &csbi);
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
    }

    void setCursorPosition(const short x, const short y)
    {
        HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(hCons, pos);
    }

} // namespace IrukakunOthello
