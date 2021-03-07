#include "Display.h"

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
        // display.setLetter(0, 0, BLACK_STONE);
        // display.setLetter(6, 7, WHITE_STONE);
        // std::cout << display.toString();
        display.initializeDisplay();
        display.setLetter(0, 0, "あ");
        display.setLetter(4, 3, FULL_WIDTH_DOT);
        display.setLetter(0, 1, "い");
        display.setLetter(0, 0, BLACK_STONE);
        display.setLetter(6, 7, WHITE_STONE);
        display.drawAll();

        char c;
        std::cin >> c;

        display.setLetter(0, 0, "鉄");
        display.draw(0, 0);

        // std::cin >> c;

        // int k = 0;
        // throw std::runtime_error("エラー発生");
        // int l = 100 / k;
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