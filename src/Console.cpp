#include "Console.h"

#include <stdexcept>
#include <iostream>

#include <windows.h>
#include <synchapi.h>

namespace IrukakunOthello
{
    namespace
    {
        DWORD fdwSaveOldMode;
        HANDLE hStdInput;

        // 直前にクリックされた座標
        short x, y;

    } // namespace

    InputType waitForInput()
    {
        INPUT_RECORD inputRecord;
        DWORD numberOfEventsRead;
        for (;;)
        {
            if (WaitForSingleObject(hStdInput, INFINITE) == WAIT_FAILED)
            {
                throw std::runtime_error("[FAILED] waitForInput : WaitForSingleObject error");
            }
            if (!PeekConsoleInput(hStdInput, &inputRecord, 1, &numberOfEventsRead))
            {
                throw std::runtime_error("[FAILED] waitForInput : PeekConsoleInput error");
            }
            if (inputRecord.EventType == KEY_EVENT)
            {
                return OTHER;
            }
            else if (inputRecord.EventType == MOUSE_EVENT)
            {
                if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    if (!ReadConsoleInput(hStdInput, &inputRecord, 1, &numberOfEventsRead))
                    {
                        throw std::runtime_error("[FAILED] waitForInput : ReadConsoleInput error");
                    }
                    x = inputRecord.Event.MouseEvent.dwMousePosition.X;
                    y = inputRecord.Event.MouseEvent.dwMousePosition.Y;
                    return LEFT_CLICK;
                }
            }

            if (!ReadConsoleInput(hStdInput, &inputRecord, 1, &numberOfEventsRead))
            {
                throw std::runtime_error("[FAILED] waitForInput : ReadConsoleInput error");
            }
        }
    }

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

    short getLastClickPositionX()
    {
        return x;
    }

    short getLastClickPositionY()
    {
        return y;
    }

    void initializeConsoleInputMode()
    {
        hStdInput = GetStdHandle(STD_INPUT_HANDLE);
        if (hStdInput == INVALID_HANDLE_VALUE)
        {
            throw std::runtime_error("[FAILED] setConsoleMode : hStdInput error");
        }
        if (!GetConsoleMode(hStdInput, &fdwSaveOldMode))
        {
            throw std::runtime_error("[FAILED] setConsoleMode : GetConsoleMode error");
        }
        DWORD fdwMode;
        fdwMode = ENABLE_ECHO_INPUT |
                  ENABLE_INSERT_MODE |
                  ENABLE_LINE_INPUT |
                  ENABLE_MOUSE_INPUT |
                  ENABLE_PROCESSED_INPUT |
                  ENABLE_EXTENDED_FLAGS;
        if (!SetConsoleMode(hStdInput, fdwMode))
        {
            throw std::runtime_error("[FAILED] setConsoleMode : SetConsoleMode error");
        }
    }

    void restoreConsoleInputMode()
    {
        SetConsoleMode(hStdInput, fdwSaveOldMode);
    }

} // namespace IrukakunOthello
