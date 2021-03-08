#include "OthelloGame.h"
#include "Display.h"

#include <assert.h>
#include <iostream>
#include <vector>

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

    bool isContain(const Square s, std::vector<Square> &validList)
    {
        for (const Square e : validList)
        {
            if (s.rowNo() == e.rowNo() && s.colNo() == e.colNo())
                return true;
        }
        return false;
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

    bool Square::isNone() const
    {
        return disk_ == NONE;
    }

    bool Square::isNullObject() const
    {
        return rowNo() <= 0 || colNo() <= 0;
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
    }

    void OthelloGame::run()
    {
        char row = ' ';
        char col = ' ';
        while (std::cin)
        {
            updateDisplay();

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
        Square s;
        s.setRowNo(squareRowNo);
        s.setColNo(squareColNo);
        s.setDisk(d);
        if (isContain(s, getValidSquareList(d)))
        {
            board_[squareRowNo - 1][squareColNo - 1].setDisk(d);
        }
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

    void OthelloGame::updateDisplay()
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

    std::vector<Square> OthelloGame::getValidSquareList(const Disk d)
    {
        std::vector<Square> result;
        for (std::size_t i = 0; i < board_.size(); i++)
        {
            for (std::size_t j = 0; j < board_[i].size(); j++)
            {
                Square s = board_[i][j];
                if (s.disk() == NONE)
                {
                    // 上方向
                    Square up = getUpSquare(s);
                    if (!up.isNullObject() && !up.isNone() && (up.disk() != d))
                    {
                        // TODO: さらにこの方向の先に自身と同じ色があるかの判定が必要
                        Square searchResult = search(&OthelloGame::getUpSquare, up, d);
                        if (!searchResult.isNullObject() && !searchResult.isNone())
                        {
                            result.push_back(s);
                            continue;
                        }
                    }

                    //std::cout << "up" << std::endl;

                    // 下方向
                    Square down = getDownSquare(s);
                    if (!down.isNullObject() && !down.isNone() && (down.disk() != d))
                    {
                        // TODO: さらにこの方向の先に自身と同じ色があるかの判定が必要
                        Square searchResult = search(&OthelloGame::getDownSquare, down, d);
                        if (!searchResult.isNullObject() && !searchResult.isNone())
                        {
                            result.push_back(s);
                            continue;
                        }
                    }

                    //std::cout << "down" << std::endl;

                    // 左方向
                    Square left = getLeftSquare(s);
                    if (!left.isNullObject() && !left.isNone() && (left.disk() != d))
                    {
                        // TODO: さらにこの方向の先に自身と同じ色があるかの判定が必要
                        Square searchResult = search(&OthelloGame::getLeftSquare, left, d);
                        if (!searchResult.isNullObject() && !searchResult.isNone())
                        {
                            result.push_back(s);
                            continue;
                        }
                    }

                    //std::cout << "left" << std::endl;

                    // 右方向
                    Square right = getRightSquare(s);
                    if (!right.isNullObject() && !right.isNone() && (right.disk() != d))
                    {
                        // TODO: さらにこの方向の先に自身と同じ色があるかの判定が必要
                        Square searchResult = search(&OthelloGame::getRightSquare, right, d);
                        if (!searchResult.isNullObject() && !searchResult.isNone())
                        {
                            result.push_back(s);
                            continue;
                        }
                    }

                    //std::cout << "right" << std::endl;

                    // 右上方向
                    Square upRight = getUpRightSquare(s);
                    if (!upRight.isNullObject() && !upRight.isNone() && (upRight.disk() != d))
                    {
                        // TODO: さらにこの方向の先に自身と同じ色があるかの判定が必要
                        Square searchResult = search(&OthelloGame::getUpRightSquare, upRight, d);
                        if (!searchResult.isNullObject() && !searchResult.isNone())
                        {
                            result.push_back(s);
                            continue;
                        }
                    }

                    //std::cout << "upRight" << std::endl;

                    // 右下方向
                    Square downRight = getDownRightSquare(s);
                    if (!downRight.isNullObject() && !downRight.isNone() && (downRight.disk() != d))
                    {
                        // TODO: さらにこの方向の先に自身と同じ色があるかの判定が必要
                        Square searchResult = search(&OthelloGame::getDownRightSquare, downRight, d);
                        if (!searchResult.isNullObject() && !searchResult.isNone())
                        {
                            result.push_back(s);
                            continue;
                        }
                    }

                    //std::cout << "downRight" << std::endl;

                    // 左上方向
                    Square upLeft = getUpLeftSquare(s);
                    if (!upLeft.isNullObject() && !upLeft.isNone() && (upLeft.disk() != d))
                    {
                        // TODO: さらにこの方向の先に自身と同じ色があるかの判定が必要
                        Square searchResult = search(&OthelloGame::getUpLeftSquare, upLeft, d);
                        if (!searchResult.isNullObject() && !searchResult.isNone())
                        {
                            result.push_back(s);
                            continue;
                        }
                    }

                    //std::cout << "upLeft" << std::endl;

                    // 左下方向
                    Square downLeft = getDownLeftSquare(s);
                    if (!downLeft.isNullObject() && !downLeft.isNone() && (downLeft.disk() != d))
                    {
                        // TODO: さらにこの方向の先に自身と同じ色があるかの判定が必要
                        Square searchResult = search(&OthelloGame::getDownLeftSquare, downLeft, d);
                        if (!searchResult.isNullObject() && !searchResult.isNone())
                        {
                            result.push_back(s);
                            continue;
                        }
                    }

                    //std::cout << "downLeft" << std::endl;
                }
            }
        }
        return result;
    }

    Square OthelloGame::getUpSquare(const Square s)
    {
        Square result;
        if (s.rowNo() <= 1)
            return result;

        return board_[s.rowNo() - 2][s.colNo() - 1];
    }

    Square OthelloGame::getDownSquare(const Square s)
    {
        Square result;
        if (s.rowNo() >= 8)
            return result;

        return board_[s.rowNo()][s.colNo() - 1];
    }

    Square OthelloGame::getLeftSquare(const Square s)
    {
        Square result;
        if (s.colNo() <= 1)
            return result;

        return board_[s.rowNo() - 1][s.colNo() - 2];
    }

    Square OthelloGame::getRightSquare(const Square s)
    {
        Square result;
        if (s.colNo() >= 8)
            return result;

        return board_[s.rowNo() - 1][s.colNo()];
    }

    Square OthelloGame::getUpRightSquare(const Square s)
    {
        Square result;
        if (getUpSquare(s).isNullObject() ||
            getRightSquare(s).isNullObject())
        {
            return result;
        }

        return board_[s.rowNo() - 2][s.colNo()];
    }

    Square OthelloGame::getDownRightSquare(const Square s)
    {
        Square result;
        if (getDownSquare(s).isNullObject() ||
            getRightSquare(s).isNullObject())
        {
            return result;
        }

        return board_[s.rowNo()][s.colNo()];
    }

    Square OthelloGame::getUpLeftSquare(const Square s)
    {
        Square result;
        if (getUpSquare(s).isNullObject() ||
            getLeftSquare(s).isNullObject())
        {
            return result;
        }

        return board_[s.rowNo() - 2][s.colNo() - 2];
    }

    Square OthelloGame::getDownLeftSquare(const Square s)
    {
        Square result;
        if (getDownSquare(s).isNullObject() ||
            getLeftSquare(s).isNullObject())
        {
            return result;
        }

        return board_[s.rowNo()][s.colNo() - 2];
    }

    Square OthelloGame::search(searchFunc f, const Square s, const Disk d)
    {
        Square result;
        Square temp = s;
        while (true)
        {
            result = (this->*f)(temp);
            temp = result;
            if (result.isNullObject() || result.isNone() || result.disk() == d)
                break;
        }
        return result;
    }

} // IrukakunOthello
