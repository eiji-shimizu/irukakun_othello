#include "Display.h"
#include "Console.h"

#include <sstream>
#include <iostream>

namespace IrukakunOthello
{
    const std::string FULL_WIDTH_SPACE = "　";
    const std::string CRLF = "\r\n";
    const std::string FULL_WIDTH_DOT = "・";
    const std::string BLACK_DISK = "●";
    const std::string WHITE_DISK = "○";
    const std::string ONE = "１";
    const std::string TWO = "２";
    const std::string THREE = "３";
    const std::string FOUR = "４";
    const std::string FIVE = "５";
    const std::string SIX = "６";
    const std::string SEVEN = "７";
    const std::string EIGHT = "８";

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

    void Display::Element::draw() const
    {
        short saveX, saveY;
        getCursorPosition(saveX, saveY);
        setCursorPosition(x_, y_);
        std::cout << letter_;
        setCursorPosition(saveX, saveY);
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
    void Display::initializeDisplay(std::string (*initialValueGenerator)(const std::size_t i, const std::size_t j))
    {
        for (std::size_t i = 0; i < data_.size(); i++)
        {
            for (std::size_t j = 0; j < data_[i].size(); j++)
            {
                // 初期表示時の表示文字を設定
                std::string s = initialValueGenerator(i, j);
                data_[i][j].setLetter(s);
                // 表示位置を退避
                short x, y;
                getCursorPosition(x, y);
                data_[i][j].setX(x);
                data_[i][j].setY(y);
                // 初期表示
                std::cout << data_[i][j].toString();
            }
        }
    }

    void Display::setLetter(std::size_t rowNo, std::size_t colNo, std::string letter)
    {
        if ((0 <= rowNo && rowNo < xUpperLimit) && (0 <= colNo && colNo < yUpperLimit))
        {
            data_[rowNo][colNo].setLetter(letter);
            return;
        }
        throw std::out_of_range("out_of_range error : (rowNo,colNo) = (" + std::to_string(rowNo) + "," + std::to_string(colNo) + ")");
    }

    void Display::draw(std::size_t rowNo, std::size_t colNo) const
    {
        if ((0 <= rowNo && rowNo < xUpperLimit) && (0 <= colNo && colNo < yUpperLimit))
        {
            data_[rowNo][colNo].draw();
            return;
        }
        throw std::out_of_range("out_of_range error : (rowNo,colNo) = (" + std::to_string(rowNo) + "," + std::to_string(colNo) + ")");
    }

    void Display::drawAll() const
    {
        for (std::size_t i = 0; i < data_.size(); i++)
        {
            for (std::size_t j = 0; j < data_[i].size(); j++)
            {
                draw(i, j);
            }
        }
    }

    void Display::getCurrentCursorPosition(short &x, short &y) const
    {
        getCursorPosition(x, y);
    }

    void Display::setCurrentCursorPosition(const short x, const short y) const
    {
        setCursorPosition(x, y);
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