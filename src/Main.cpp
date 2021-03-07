#include "Display.h"
#include "OthelloGame.h"

#include <iostream>
#include <vector>
#include <string>
#include <exception>

#include <windows.h>

using namespace IrukakunOthello;

int main()
{
    try
    {
        Display display;
        OthelloGame game(display);
        game.initialize();
        game.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unexpected error." << std::endl;
    }
}