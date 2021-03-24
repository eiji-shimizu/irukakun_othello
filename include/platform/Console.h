#ifndef IRUKAKUN_OTHELLO_Console_INCLUDED
#define IRUKAKUN_OTHELLO_Console_INCLUDED

#include <windows.h>

namespace IrukakunOthello
{
    enum InputType
    {
        LEFT_CLICK,
        OTHER
    };

    InputType waitForInput();
    void getCursorPosition(short &x, short &y);
    void setCursorPosition(const short x, const short y);
    short getLastClickPositionX();
    short getLastClickPositionY();
    void initializeConsoleInputMode();
    void restoreConsoleInputMode();

} // namespace IrukakunOthello

#endif // IRUKAKUN_OTHELLO_Console_INCLUDED
