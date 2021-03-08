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
    std::string convertForDisplay(const Disk d)
    {
        switch (d)
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
                return Display::FULL_WIDTH_SPACE;
        }
        else if (i == 4)
        {
            if (j == 0)
                return getNumberStr(i);
            else if (j == 9)
                return Display::CRLF;
            else
                return Display::FULL_WIDTH_SPACE;
        }
        else if (i == 5)
        {
            if (j == 0)
                return getNumberStr(i);
            else if (j == 9)
                return Display::CRLF;
            else
                return Display::FULL_WIDTH_SPACE;
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

    Square::Square()
        : disk_(NONE),
          rowNo_(0),
          colNo_(0)
    {
    }

    void Square::setDisk(Disk d)
    {
        disk_ = d;
    }

    void Square::setRowNo(short s)
    {
        rowNo_ = s;
    }

    void Square::setColNo(short s)
    {
        colNo_ = s;
    }

    Disk Square::disk() const
    {
        return disk_;
    }

    short Square::rowNo() const
    {
        return rowNo_;
    }

    short Square::colNo() const
    {
        return colNo_;
    }

    OthelloGame::OthelloGame(Display &d)
        : display_(d),
          playerDisk_(BLACK)
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
        boardInitialize();
        update();
    }

    void OthelloGame::run()
    {
        char row = ' ';
        char col = ' ';
        while (std::cin)
        {
            update();

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
        putDisk(squareRowNo, squareColNo, playerDisk_);
    }

    void OthelloGame::putDisk(const short squareRowNo, const short squareColNo, const Disk d)
    {
        assert((1 <= squareRowNo && squareRowNo <= rowNoUpperLimit));
        assert((1 <= squareColNo && squareColNo <= colNoUpperLimit));
        // TODO: オセロゲームとして有効な手かどうかの入力チェック
        board_[squareRowNo - 1][squareColNo - 1].setDisk(d);
    }

    void OthelloGame::reDraw(const short squareRowNo, const short squareColNo)
    {
        assert((1 <= squareRowNo && squareRowNo <= rowNoUpperLimit));
        assert((1 <= squareColNo && squareColNo <= colNoUpperLimit));
        short rowNo = squareRowNo;
        short colNo = squareColNo;
        convertForDisplay(rowNo, colNo);
        display_.draw(rowNo, colNo);
    }

    void OthelloGame::boardInitialize()
    {
        for (std::size_t i = 0; i < board_.size(); i++)
        {
            for (std::size_t j = 0; j < board_[i].size(); j++)
            {
                board_[i][j].setRowNo(i + 1);
                board_[i][j].setColNo(j + 1);

                if ((0 <= i && i <= 2) || (5 <= i && i <= 7))
                {
                    board_[i][j].setDisk(NONE);
                }
                else if (i == 3)
                {
                    if (j == 3)
                        board_[i][j].setDisk(BLACK);
                    else if (j == 4)
                        board_[i][j].setDisk(WHITE);
                    else
                        board_[i][j].setDisk(NONE);
                }
                else
                {
                    // i == 4
                    if (j == 3)
                        board_[i][j].setDisk(WHITE);
                    else if (j == 4)
                        board_[i][j].setDisk(BLACK);
                    else
                        board_[i][j].setDisk(NONE);
                }
            }
        }
    }

    void OthelloGame::sendDataToDisplay(const short squareRowNo, const short squareColNo)
    {
        assert((1 <= squareRowNo && squareRowNo <= rowNoUpperLimit));
        assert((1 <= squareColNo && squareColNo <= colNoUpperLimit));
        Square s = board_[squareRowNo - 1][squareColNo - 1];
        short rowNo = s.rowNo();
        short colNo = s.colNo();
        convertForDisplay(rowNo, colNo);
        display_.setLetter(rowNo, colNo, convertForDisplay(s.disk()));
    }

    void OthelloGame::update()
    {
        for (std::size_t i = 0; i < board_.size(); i++)
        {
            for (std::size_t j = 0; j < board_[i].size(); j++)
            {
                sendDataToDisplay(board_[i][j].rowNo(), board_[i][j].colNo());
                reDraw(board_[i][j].rowNo(), board_[i][j].colNo());
            }
        }
    }

} // IrukakunOthello
