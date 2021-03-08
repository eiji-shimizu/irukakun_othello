#ifndef IRUKAKUN_OTHELLO_OthelloGame_INCLUDED
#define IRUKAKUN_OTHELLO_OthelloGame_INCLUDED

#include <array>
#include <vector>
namespace IrukakunOthello
{
    enum Disk
    {
        BLACK,
        WHITE,
        NONE,
        RED // assert確認用,後に消す
    };

    class Square
    {
    public:
        Square();
        ~Square() = default;

        Square(const Square &) = default;
        Square &operator=(const Square &) = default;
        Square(Square &&) = default;
        Square &operator=(Square &&) = default;

        void setDisk(Disk d);
        void setRowNo(short s);
        void setColNo(short s);

        Disk disk() const;
        short rowNo() const;
        short colNo() const;

        // DiskにNONEが設定されている場合にtrue
        bool isNone() const;
        // rowNoとcolNoのどちらか一方でも0以下ならばtrue
        bool isNullObject() const;

    private:
        Disk disk_;
        short rowNo_, colNo_;
    };

    class Display;

    class OthelloGame
    {
    public:
        // 入力コマンド文字
        static const char QUIT;

        OthelloGame(Display &d);
        OthelloGame() = delete;
        ~OthelloGame();

        // コピー禁止
        OthelloGame(const OthelloGame &) = delete;
        OthelloGame &operator=(const OthelloGame &) = delete;
        // ムーブ禁止
        OthelloGame(OthelloGame &&) = delete;
        OthelloGame &operator=(OthelloGame &&) = delete;

        // 初期化処理
        void initialize();
        // オセロゲームを開始する.
        void run();

    private:
        static const int rowNoUpperLimit = 8;
        static const int colNoUpperLimit = 8;
        using OthelloBoard = std::array<std::array<Square, rowNoUpperLimit>, colNoUpperLimit>;

        // オセロのボードを初期化する
        void boardInitialize();
        // オセロのボードの内容でディスプレイを更新する
        void updateDisplay();

        // 指定された升目の内容をディスプレイクラスに送る
        void sendDataToDisplay(const short squareRowNo, const short squareColNo);
        // 指定された升目の内容を再描画する
        void reDraw(const short squareRowNo, const short squareColNo);

        // 指定された升目にプレイヤーの色の石を設定する.
        // 升目は左上から順に(行,列)で(1,1)(1,2) ... (1,8)
        // (8,1)(8,2)...(8,8)と右下に向かって指定する.
        void putDisk(const short squareRowNo, const short squareColNo);
        // 第3引数で指定された色の石を指定された升目に設定する
        void putDisk(const short squareRowNo, const short squareColNo, const Disk d);
        // 指定された色の石が置ける升のリストを返す
        std::vector<Square> getValidSquareList(const Disk d);

        // それぞれ引数の上下左右のSquareを返す
        Square getUpSquare(const Square s);
        Square getDownSquare(const Square s);
        Square getLeftSquare(const Square s);
        Square getRightSquare(const Square s);
        // それぞれ引数の右上,右下,左上,左下のSquareを返す
        Square getUpRightSquare(const Square s);
        Square getDownRightSquare(const Square s);
        Square getUpLeftSquare(const Square s);
        Square getDownLeftSquare(const Square s);
        // 上記8つの関数どれかを引数にとり,第2引数に適用する
        // その戻り値にまた適用していき,第3引数と一致するDiskを持つSquareが見つかればそれを返す
        // ただしその過程でSquare::isNoneまたはSquare::isNullObjectがtrueとなるSquareがあればそれを返す
        using searchFunc = Square (OthelloGame::*)(const Square s);
        Square search(searchFunc f, const Square s, const Disk d);

        // ディスプレイへの参照
        Display &display_;
        // オセロのボード
        OthelloBoard board_;
        // プレイヤーの石の色
        Disk playerDisk_;
        // 対戦相手の石の色
        Disk opponentDisk_;
        // コンソール上の入力開始位置
        short startX_, startY_;
    };

} // namespace IrukakunOthello

#endif // IRUKAKUN_OTHELLO_OthelloGame_INCLUDED
