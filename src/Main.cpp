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
        // std::cout << display.toString();
        // std::cout << std::endl;
        // display.setLetter(0, 0, "あ");
        // display.setLetter(4, 3, FULL_WIDTH_DOT);
        // display.setLetter(0, 1, "い");
        // display.setLetter(0, 0, BLACK_DISK);
        // display.setLetter(6, 7, WHITE_DISK);
        // std::cout << display.toString();

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