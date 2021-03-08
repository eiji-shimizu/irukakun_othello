#include "Console.h"

#include <stdexcept>

#include <windows.h>

namespace IrukakunOthello
{
    void getCursorPosition(short &x, short &y)
    {
        HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(hCons, &csbi))
        {
            throw std::runtime_error("[FAILED] getCursorPosition : GetConsoleScreenBufferInfo error");
        }
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
    }

    void setCursorPosition(const short x, const short y)
    {
        HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.X = x;
        pos.Y = y;
        if (!SetConsoleCursorPosition(hCons, pos))
        {
            throw std::runtime_error("[FAILED] setCursorPosition : SetConsoleCursorPosition error");
        }
    }

} // namespace IrukakunOthello
