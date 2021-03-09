#include "OthelloGame.h"
#include "Display.h"

#include <assert.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

namespace IrukakunOthello
{
    // コマンド文字
    const char OthelloGame::QUIT = 'q';

    namespace
    {
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

        // それぞれ引数の上下左右のSquareを返す
        Square getUpSquare(OthelloGame::OthelloBoard &board, const Square s)
        {
            Square result;
            if (s.rowNo() <= 1)
                return result;

            return board[s.rowNo() - 2][s.colNo() - 1];
        }

        Square getDownSquare(OthelloGame::OthelloBoard &board, const Square s)
        {
            Square result;
            if (s.rowNo() >= 8)
                return result;

            return board[s.rowNo()][s.colNo() - 1];
        }

        Square getLeftSquare(OthelloGame::OthelloBoard &board, const Square s)
        {
            Square result;
            if (s.colNo() <= 1)
                return result;

            return board[s.rowNo() - 1][s.colNo() - 2];
        }

        Square getRightSquare(OthelloGame::OthelloBoard &board, const Square s)
        {
            Square result;
            if (s.colNo() >= 8)
                return result;

            return board[s.rowNo() - 1][s.colNo()];
        }

        // それぞれ引数の右上,右下,左上,左下のSquareを返す
        Square getUpRightSquare(OthelloGame::OthelloBoard &board, const Square s)
        {
            Square result;
            if (getUpSquare(board, s).isNullObject() ||
                getRightSquare(board, s).isNullObject())
            {
                return result;
            }

            return board[s.rowNo() - 2][s.colNo()];
        }

        Square getDownRightSquare(OthelloGame::OthelloBoard &board, const Square s)
        {
            Square result;
            if (getDownSquare(board, s).isNullObject() ||
                getRightSquare(board, s).isNullObject())
            {
                return result;
            }

            return board[s.rowNo()][s.colNo()];
        }

        Square getUpLeftSquare(OthelloGame::OthelloBoard &board, const Square s)
        {
            Square result;
            if (getUpSquare(board, s).isNullObject() ||
                getLeftSquare(board, s).isNullObject())
            {
                return result;
            }

            return board[s.rowNo() - 2][s.colNo() - 2];
        }

        Square getDownLeftSquare(OthelloGame::OthelloBoard &board, const Square s)
        {
            Square result;
            if (getDownSquare(board, s).isNullObject() ||
                getLeftSquare(board, s).isNullObject())
            {
                return result;
            }

            return board[s.rowNo()][s.colNo() - 2];
        }

        using searchFunc = Square (*)(OthelloGame::OthelloBoard &board, const Square s);
        // searchFuncとして,上記8つの関数どれかを引数にとり,引数sに適用する
        // その戻り値にまた適用していき,引数dと一致するDiskを持つSquareが見つかればそれを返す
        // ただしその過程でSquare::isNoneまたはSquare::isNullObjectがtrueとなるSquareがあればそれを返す
        Square search(searchFunc f, OthelloGame::OthelloBoard &board, const Square s, const Disk d)
        {
            Square result;
            Square temp = s;
            while (true)
            {
                result = f(board, temp);
                temp = result;
                if (result.isNullObject() || result.isNone() || result.disk() == d)
                    break;
            }
            return result;
        }

        // 引数のSquareの状態で新たに石が置かれたとみなし,その結果として裏返される石の数を返す.
        // eFlagがtrueの場合はその過程で実際に石を裏返す.
        short reverseImpl(OthelloGame::OthelloBoard &board, const Square s, bool eFlag)
        {
            short result = 0;
            // 上方向
            Square searchResult = search(getUpSquare, board, s, s.disk());
            if (!searchResult.isNullObject() && !searchResult.isNone())
            {
                short temp = std::abs(searchResult.rowNo() - s.rowNo()) - 1;
                result += temp;
                if (eFlag)
                {
                    Square target = s;
                    for (; temp > 0; temp--)
                    {
                        target = getUpSquare(board, target);
                        board[target.rowNo() - 1][target.colNo() - 1].setDisk(s.disk());
                        board[target.rowNo() - 1][target.colNo() - 1].setUpdate(true);
                    }
                }
            }

            //std::cout << "up" << std::endl;

            // 下方向
            searchResult = search(getDownSquare, board, s, s.disk());
            if (!searchResult.isNullObject() && !searchResult.isNone())
            {
                short temp = std::abs(searchResult.rowNo() - s.rowNo()) - 1;
                result += temp;
                if (eFlag)
                {
                    Square target = s;
                    for (; temp > 0; temp--)
                    {
                        target = getDownSquare(board, target);
                        board[target.rowNo() - 1][target.colNo() - 1].setDisk(s.disk());
                        board[target.rowNo() - 1][target.colNo() - 1].setUpdate(true);
                    }
                }
            }

            //std::cout << "down" << std::endl;

            // 左方向
            searchResult = search(getLeftSquare, board, s, s.disk());
            if (!searchResult.isNullObject() && !searchResult.isNone())
            {
                short temp = std::abs(searchResult.colNo() - s.colNo()) - 1;
                result += temp;
                if (eFlag)
                {
                    Square target = s;
                    for (; temp > 0; temp--)
                    {
                        target = getLeftSquare(board, target);
                        board[target.rowNo() - 1][target.colNo() - 1].setDisk(s.disk());
                        board[target.rowNo() - 1][target.colNo() - 1].setUpdate(true);
                    }
                }
            }

            //std::cout << "left" << std::endl;

            // 右方向
            searchResult = search(getRightSquare, board, s, s.disk());
            if (!searchResult.isNullObject() && !searchResult.isNone())
            {
                short temp = std::abs(searchResult.colNo() - s.colNo()) - 1;
                result += temp;
                if (eFlag)
                {
                    Square target = s;
                    for (; temp > 0; temp--)
                    {
                        target = getRightSquare(board, target);
                        board[target.rowNo() - 1][target.colNo() - 1].setDisk(s.disk());
                        board[target.rowNo() - 1][target.colNo() - 1].setUpdate(true);
                    }
                }
            }

            //std::cout << "right" << std::endl;

            // 右上方向
            searchResult = search(getUpRightSquare, board, s, s.disk());
            if (!searchResult.isNullObject() && !searchResult.isNone())
            {
                short temp = std::abs(searchResult.colNo() - s.colNo()) - 1;
                result += temp;
                if (eFlag)
                {
                    Square target = s;
                    for (; temp > 0; temp--)
                    {
                        target = getUpRightSquare(board, target);
                        board[target.rowNo() - 1][target.colNo() - 1].setDisk(s.disk());
                        board[target.rowNo() - 1][target.colNo() - 1].setUpdate(true);
                    }
                }
            }

            //std::cout << "upRight" << std::endl;

            // 右下方向
            searchResult = search(getDownRightSquare, board, s, s.disk());
            if (!searchResult.isNullObject() && !searchResult.isNone())
            {
                short temp = std::abs(searchResult.colNo() - s.colNo()) - 1;
                result += temp;
                if (eFlag)
                {
                    Square target = s;
                    for (; temp > 0; temp--)
                    {
                        target = getDownRightSquare(board, target);
                        board[target.rowNo() - 1][target.colNo() - 1].setDisk(s.disk());
                        board[target.rowNo() - 1][target.colNo() - 1].setUpdate(true);
                    }
                }
            }

            //std::cout << "downRight" << std::endl;

            // 左上方向
            searchResult = search(getUpLeftSquare, board, s, s.disk());
            if (!searchResult.isNullObject() && !searchResult.isNone())
            {
                short temp = std::abs(searchResult.colNo() - s.colNo()) - 1;
                result += temp;
                if (eFlag)
                {
                    Square target = s;
                    for (; temp > 0; temp--)
                    {
                        target = getUpLeftSquare(board, target);
                        board[target.rowNo() - 1][target.colNo() - 1].setDisk(s.disk());
                        board[target.rowNo() - 1][target.colNo() - 1].setUpdate(true);
                    }
                }
            }

            //std::cout << "upLeft" << std::endl;

            // 左下方向
            searchResult = search(getDownLeftSquare, board, s, s.disk());
            if (!searchResult.isNullObject() && !searchResult.isNone())
            {
                short temp = std::abs(searchResult.colNo() - s.colNo()) - 1;
                result += temp;
                if (eFlag)
                {
                    Square target = s;
                    for (; temp > 0; temp--)
                    {
                        target = getDownLeftSquare(board, target);
                        board[target.rowNo() - 1][target.colNo() - 1].setDisk(s.disk());
                        board[target.rowNo() - 1][target.colNo() - 1].setUpdate(true);
                    }
                }
            }

            //std::cout << "downLeft" << std::endl;
            //std::cout << result << std::endl;

            return result;
        }

        short reverseImpl(const OthelloGame::OthelloBoard &board, const Square s)
        {
            return reverseImpl(const_cast<OthelloGame::OthelloBoard &>(board), s, false);
        }

        short reverseImpl(OthelloGame::OthelloBoard &board, const Square s)
        {
            return reverseImpl(board, s, true);
        }

    } // namespace

    /* Square class */
    Square::Square()
        : disk_(NONE),
          rowNo_(0),
          colNo_(0),
          update_(true)
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

    void Square::setUpdate(bool b)
    {
        update_ = b;
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

    bool Square::isUpdate() const
    {
        return update_;
    }

    bool Square::isNone() const
    {
        return disk_ == NONE;
    }

    bool Square::isNullObject() const
    {
        return rowNo() <= 0 || colNo() <= 0;
    }

    /* OthelloGame class */
    OthelloGame::OthelloGame(Display &d)
        : display_(d),
          playerDisk_(BLACK),
          opponentDisk_(WHITE),
          playerTurn_(true)
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
        // 最後に石が置かれた升を設定する
        Square last;
        while (std::cin)
        {
            updateDisplay();

            if (!last.isNullObject())
            {
                // 即座に裏返した内容が描画されないようにスリープする
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                reverse(last);
                last = Square();
                // ターンを入れ替える
                playerTurn_ = !playerTurn_;
                continue;
            }

            if (playerTurn_)
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
                    // 行列入力時
                    short rowNo = std::stoi(std::string{row});
                    short colNo = std::stoi(std::string{col});
                    if (0 < rowNo && rowNo < 9 && 0 < colNo && colNo < 9)
                    {
                        last = putDisk(rowNo, colNo, playerDisk_);
                    }
                }
                else
                {
                    // コマンド入力時
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
            }
            else
            {
                std::vector<Square> list = getValidSquareList(opponentDisk_);
                if (list.size() > 0)
                {
                    Square choice = list[0];
                    // 即座に相手の手の内容が出力されないようにスリープする
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    last = putDisk(choice.rowNo(), choice.colNo(), opponentDisk_);
                }
            }

            display_.setCurrentCursorPosition(startX_, startY_);
        }
        if (!std::cin)
        {
            throw std::runtime_error("[FAILED] OthelloGame::run : std::cin error");
        }
    }

    Square OthelloGame::putDisk(const short squareRowNo, const short squareColNo, const Disk d)
    {
        assert((1 <= squareRowNo && squareRowNo <= rowNoUpperLimit));
        assert((1 <= squareColNo && squareColNo <= colNoUpperLimit));
        if (board_[squareRowNo - 1][squareColNo - 1].disk() == NONE)
        {
            Square s;
            s.setRowNo(squareRowNo);
            s.setColNo(squareColNo);
            s.setDisk(d);
            if (tryReverse(s) > 0)
            {
                board_[squareRowNo - 1][squareColNo - 1].setDisk(d);
                board_[squareRowNo - 1][squareColNo - 1].setUpdate(true);
                return s;
            }
        }
        return Square();
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
                if (board_[i][j].isUpdate())
                {
                    sendDataToDisplay(board_[i][j].rowNo(), board_[i][j].colNo());
                    reDraw(board_[i][j].rowNo(), board_[i][j].colNo());
                    board_[i][j].setUpdate(false);
                }
            }
        }
    }

    short OthelloGame::tryReverse(const Square s) const
    {
        return reverseImpl(board_, s);
    }

    short OthelloGame::reverse(const Square s)
    {
        return reverseImpl(board_, s);
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
                    s.setDisk(d);
                    if (tryReverse(s) > 0)
                    {
                        result.push_back(s);
                        continue;
                    }
                }
            }
        }
        return result;
    }

} // IrukakunOthello
