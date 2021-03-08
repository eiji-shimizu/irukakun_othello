#include "OthelloGame.h"
#include "Display.h"

#include <assert.h>
#include <iostream>

namespace IrukakunOthello
{
    const char OthelloGame::QUIT = 'q';

    std::string getNumberStr(const int i)
    {

        if (i == 1)
            return Display::ONE;
        else if (i == 2)
            return Display::TWO;
        else if (i == 3)
            return Display::THREE;
        else if (i == 4)
            return Display::FOUR;
        else if (i == 5)
            return Display::FIVE;
        else if (i == 6)
            return Display::SIX;
        else if (i == 7)
            return Display::SEVEN;
        else if (i == 8)
            return Display::EIGHT;
        else
            return "";
    }

    // オセロの升目の行列指定の値を引数にとり
    // その値をDisplayクラスのための対応する値に変換する
    // 現状では両者の指定が一致しているので処理は無い
    void convertForDisplay(short &rowNo, short &colNo)
    {
        // 必要になれば処理追加
    }

    // オセロの石の色をDisplayクラスのための対応する文字列に変換して返す
    std::string convertForDisplay(const Color c)
    {
        switch (c)
        {
        case BLACK:
            return Display::BLACK_DISK;
        case WHITE:
            return Display::WHITE_DISK;
        case NONE:
            return Display::FULL_WIDTH_DOT;
        }
        assert(false);
        return "";
    }

    // この関数はDisplayクラスから呼ばれる
    // Displayクラスの2次元配列の添え字[i][j]が引数に入力される
    // その要素[i][j]に初期表示値として表示したい内容を返す.
    std::string initialValueGenerator(const std::size_t i, const std::size_t j)
    {
        if (i == 0)
        {
            if (j == 0)
                return Display::FULL_WIDTH_SPACE;
            else if (j == 9)
                return Display::CRLF;
            else
                return getNumberStr(j);
        }
        else if ((1 <= i && i <= 3) || (6 <= i && i <= 8))
        {
            if (j == 0)
                return getNumberStr(i);
            else if (j == 9)
                return Display::CRLF;
            else
                return Display::FULL_WIDTH_DOT;
        }
        else if (i == 4)
        {
            if (j == 0)
                return getNumberStr(i);
            else if (j == 9)
                return Display::CRLF;
            else if ((1 <= j && j <= 3) || (6 <= j && j <= 8))
                return Display::FULL_WIDTH_DOT;
            else if (j == 4)
                return Display::BLACK_DISK;
            else if (j == 5)
                return Display::WHITE_DISK;
        }
        else if (i == 5)
        {
            if (j == 0)
                return getNumberStr(i);
            else if (j == 9)
                return Display::CRLF;
            else if ((1 <= j && j <= 3) || (6 <= j && j <= 8))
                return Display::FULL_WIDTH_DOT;
            else if (j == 4)
                return Display::WHITE_DISK;
            else if (j == 5)
                return Display::BLACK_DISK;
        }
        else
        {
            // i == 9
            if (j == 9)
                return Display::CRLF;
            else
                return Display::FULL_WIDTH_SPACE;
        }
        assert(false);
        return "";
    }

    OthelloGame::OthelloGame(Display &d)
        : display_(d),
          playerColor_(BLACK)
    {
    }

    OthelloGame::~OthelloGame()
    {
        // noop
    }

    void OthelloGame::initialize()
    {
        display_.initializeDisplay(initialValueGenerator);
        display_.getCurrentCursorPosition(startX_, startY_);
    }

    void OthelloGame::run()
    {
        char row = ' ';
        char col = ' ';
        while (std::cin)
        {
            std::cin >> row;
            if (!std::cin)
            {
                break;
            }
            if (std::isdigit(row))
            {
                std::cin >> col;
            }
            if (!std::cin)
            {
                break;
            }

            if (std::isdigit(row) && std::isdigit(col))
            {
                short rowNo = std::stoi(std::string{row});
                short colNo = std::stoi(std::string{col});
                if (0 < rowNo && rowNo < 9 && 0 < colNo && colNo < 9)
                {
                    putDisk(rowNo, colNo);
                    reDraw(rowNo, colNo);
                }
            }
            else
            {
                char c = row;
                if (std::isdigit(c))
                {
                    c = col;
                }
                switch (c)
                {
                case QUIT:
                    return;
                }
            }
            display_.setCurrentCursorPosition(startX_, startY_);
        }
        if (!std::cin)
        {
            throw std::runtime_error("[FAILED] OthelloGame::run : std::cin error");
        }
    }

    void OthelloGame::putDisk(const short squareRowNo, const short squareColNo)
    {
        putDisk(squareRowNo, squareColNo, playerColor_);
    }

    void OthelloGame::putDisk(const short squareRowNo, const short squareColNo, const Color c)
    {
        short rowNo = squareRowNo;
        short colNo = squareColNo;
        convertForDisplay(rowNo, colNo);
        display_.setLetter(rowNo, colNo, convertForDisplay(c));
    }

    void OthelloGame::reDraw(const short squareRowNo, const short squareColNo)
    {
        short rowNo = squareRowNo;
        short colNo = squareColNo;
        convertForDisplay(rowNo, colNo);
        display_.draw(rowNo, colNo);
    }

} // IrukakunOthello
