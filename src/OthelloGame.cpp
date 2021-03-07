#include "OthelloGame.h"
#include "Display.h"

namespace IrukakunOthello
{
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
            return BLACK_DISK;
        case WHITE:
            return WHITE_DISK;
        }
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
