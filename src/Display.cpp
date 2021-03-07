#include "Display.h"
#include "Console.h"

#include <sstream>
#include <iostream>

namespace IrukakunOthello
{
    const std::string FULL_WIDTH_SPACE = "　";
    const std::string CRLF = "\r\n";
    const std::string FULL_WIDTH_DOT = "・";
    const std::string BLACK_STONE = "●";
    const std::string WHITE_STONE = "○";
    const std::string ONE = "１";
    const std::string TWO = "２";
    const std::string THREE = "３";
    const std::string FOUR = "４";
    const std::string FIVE = "５";
    const std::string SIX = "６";
    const std::string SEVEN = "７";
    const std::string EIGHT = "８";

    std::string getNumberStr(const int i)
    {

        if (i == 1)
            return ONE;
        else if (i == 2)
            return TWO;
        else if (i == 3)
            return THREE;
        else if (i == 4)
            return FOUR;
        else if (i == 5)
            return FIVE;
        else if (i == 6)
            return SIX;
        else if (i == 7)
            return SEVEN;
        else if (i == 8)
            return EIGHT;
        else
            return "";
    }

    Display::Element::Element(std::string letter, short x, short y)
        : letter_(letter),
          x_(x),
          y_(y)
    {
    }

    Display::Element::Element(std::string letter)
        : letter_(letter),
          x_(0),
          y_(0)
    {
    }

    Display::Element::Element()
        : letter_(FULL_WIDTH_SPACE),
          x_(0),
          y_(0)
    {
    }

    Display::Element::~Element()
    {
        // noop
    }

    void Display::Element::setLetter(std::string letter)
    {
        letter_ = letter;
    }

    void Display::Element::setX(short x)
    {
        x_ = x;
    }

    void Display::Element::setY(short y)
    {
        y_ = y;
    }

    std::string Display::Element::toString() const
    {
        return letter_;
    }

    Display::Display()
    {
        // noop
    }

    Display::~Display()
    {
        // noop
    }

    /*
    各要素をオセロゲーム用に初期表示する.
    各要素表示直前にカーソル位置を取得して各要素の表示位置を設定する.
    */
    void Display::initializeDisplay()
    {
        for (std::size_t i = 0; i < data_.size(); i++)
        {
            for (std::size_t j = 0; j < data_[i].size(); j++)
            {
                // 初期表示時の表示文字を設定
                if (i == 0)
                {
                    if (j == 0)
                        data_[i][j].setLetter(FULL_WIDTH_SPACE);
                    else if (j == 9)
                        data_[i][j].setLetter(CRLF);
                    else
                        data_[i][j].setLetter(getNumberStr(j));
                }
                else if ((1 <= i && i <= 3) || (6 <= i && i <= 8))
                {
                    if (j == 0)
                        data_[i][j].setLetter(getNumberStr(i));
                    else if (j == 9)
                        data_[i][j].setLetter(CRLF);
                    else
                        data_[i][j].setLetter(FULL_WIDTH_DOT);
                }
                else if (i == 4)
                {
                    if (j == 0)
                        data_[i][j].setLetter(getNumberStr(i));
                    else if (j == 9)
                        data_[i][j].setLetter(CRLF);
                    else if ((1 <= j && j <= 3) || (6 <= j && j <= 8))
                        data_[i][j].setLetter(FULL_WIDTH_DOT);
                    else if (j == 4)
                        data_[i][j].setLetter(BLACK_STONE);
                    else if (j == 5)
                        data_[i][j].setLetter(WHITE_STONE);
                }
                else if (i == 5)
                {
                    if (j == 0)
                        data_[i][j].setLetter(getNumberStr(i));
                    else if (j == 9)
                        data_[i][j].setLetter(CRLF);
                    else if ((1 <= j && j <= 3) || (6 <= j && j <= 8))
                        data_[i][j].setLetter(FULL_WIDTH_DOT);
                    else if (j == 4)
                        data_[i][j].setLetter(WHITE_STONE);
                    else if (j == 5)
                        data_[i][j].setLetter(BLACK_STONE);
                }
                else
                {
                    // i == 9
                    if (j == 0)
                        data_[i][j].setLetter(CRLF);
                    else
                        data_[i][j].setLetter(FULL_WIDTH_SPACE);
                }

                short x, y;
                getCursorPosition(x, y);
                data_[i][j].setX(x);
                data_[i][j].setY(y);
                std::cout << data_[i][j].toString();
            }
        }
    }

    void Display::setLetter(std::size_t rowNo, std::size_t colNo, std::string letter)
    {
        data_[rowNo][colNo].setLetter(letter);
    }

    std::string Display::toString() const
    {
        std::ostringstream oss;
        for (std::size_t i = 0; i < data_.size(); i++)
        {
            for (std::size_t j = 0; j < data_[i].size(); j++)
            {
                oss << data_[i][j].toString();
            }
        }
        return oss.str();
    }

} // namespace IrukakunOthello