#include "Console.h"

#include <stdexcept>
#include <iostream>

#include <windows.h>
#include <synchapi.h>

namespace IrukakunOthello
{
    namespace
    {

        void setConsoleMode()
        {
            HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
            if (hStdInput == INVALID_HANDLE_VALUE)
            {
                throw std::runtime_error("[FAILED] setConsoleMode : hStdInput error");
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

    } // namespace

    InputType waitForInput()
    {
        HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
        if (hStdInput == INVALID_HANDLE_VALUE)
        {
            throw std::runtime_error("[FAILED] waitForInput : hStdInput error");
        }

        setConsoleMode();

        INPUT_RECORD inputRecord;
        DWORD numberOfEventsRead;
        for (;;)
        {
            if (WaitForSingleObject(hStdInput, INFINITE) == WAIT_FAILED)
            {
                throw std::runtime_error("[FAILED] waitForInput : WaitForSingleObject error");
            }
            //std::cout << "WaitForSingleObject end" << std::endl;
            if (!PeekConsoleInput(hStdInput, &inputRecord, 1, &numberOfEventsRead))
            {
                throw std::runtime_error("[FAILED] waitForInput : ReadConsoleInput error");
            }
            //std::cout << "PeekConsoleInput end" << std::endl;
            if (inputRecord.EventType == KEY_EVENT)
            {
                std::cout << "KEY_EVENT" << std::endl;
                return OTHER;
            }
            else if (inputRecord.EventType == MOUSE_EVENT)
            {
                //std::cout << "MOUSE_EVENT" << std::endl;
                if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    if (!ReadConsoleInput(hStdInput, &inputRecord, 1, &numberOfEventsRead))
                    {
                        throw std::runtime_error("[FAILED] waitForInput : ReadConsoleInput error");
                    }
                    return LEFT_CLICK;
                }
            }
            // else if (inputRecord.EventType == WINDOW_BUFFER_SIZE_EVENT)
            // {
            //     std::cout << "WINDOW_BUFFER_SIZE_EVENT" << std::endl;
            // }
            // else if (inputRecord.EventType == FOCUS_EVENT)
            // {
            //     std::cout << "FOCUS_EVENT" << std::endl;
            // }
            // else
            // {
            //     std::cout << "DEFAULT" << std::endl;
            // }

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

} // namespace IrukakunOthello
