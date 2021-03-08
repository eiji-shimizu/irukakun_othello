#ifndef IRUKAKUN_OTHELLO_OthelloGame_INCLUDED
#define IRUKAKUN_OTHELLO_OthelloGame_INCLUDED

#include <array>
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
        Square(Square &&) = delete;
        Square &operator=(Square &&) = default;

        void setDisk(Disk d);
        void setRowNo(short s);
        void setColNo(short s);

        Disk disk() const;
        short rowNo() const;
        short colNo() const;

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
        // オセロのボードを初期化する
        void boardInitialize();
        // オセロのボードの内容でディスプレイを更新する
        void update();

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

        static const int rowNoUpperLimit = 8;
        static const int colNoUpperLimit = 8;

        // ディスプレイへの参照
        Display &display_;
        // オセロのボード
        std::array<std::array<Square, rowNoUpperLimit>, colNoUpperLimit> board_;
        // プレイヤーの石の色
        Disk playerDisk_;
        // 対戦相手の石の色
        Disk opponentDisk_;
        // コンソール上の入力開始位置
        short startX_, startY_;
    };

} // namespace IrukakunOthello

#endif // IRUKAKUN_OTHELLO_OthelloGame_INCLUDED
