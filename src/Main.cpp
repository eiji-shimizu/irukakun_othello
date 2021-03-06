#include "Display.h"

#include <iostream>
#include <vector>
#include <string>

using namespace IrukakunOthello;

int main()
{
    Display display;
    std::cout << display.toString();
    std::cout << std::endl;
    display.setLetter(0, 0, "あ");
    display.setLetter(4, 3, FULL_WIDTH_DOT);
    display.setLetter(0, 1, "い");
    display.setLetter(0, 0, BLACK_STONE);
    display.setLetter(6, 7, WHITE_STONE);
    std::cout << display.toString();
}