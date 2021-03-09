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
        void setUpdate(bool b);

        Disk disk() const;
        short rowNo() const;
        short colNo() const;
        bool isUpdate() const;

        // DiskにNONEが設定されている場合にtrue
        bool isNone() const;
        // rowNoとcolNoのどちらか一方でも0以下ならばtrue
        bool isNullObject() const;

    private:
        Disk disk_;
        short rowNo_, colNo_;
        // 内容(石の有無,石の色等)が更新された場合にtrueが設定される
        // 内容をディスプレイに送った場合はfalseに戻る
        bool update_;
    };

    class Display;

    class OthelloGame
    {
    public:
        static const int rowNoUpperLimit = 8;
        static const int colNoUpperLimit = 8;
        using OthelloBoard = std::array<std::array<Square, rowNoUpperLimit>, colNoUpperLimit>;

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
        void updateDisplay();

        // 指定された升目の内容をディスプレイクラスに送る
        void sendDataToDisplay(const short squareRowNo, const short squareColNo);
        // 指定された升目の内容を再描画する
        void reDraw(const short squareRowNo, const short squareColNo);

        // 第3引数で指定された色の石を指定された升目に設定する.
        // 升目は左上から順に(行,列)で(1,1)(1,2) ... (1,8)
        // (8,1)(8,2)...(8,8)と右下に向かって指定する.
        // 戻り値:置いた升目のSquareオブジェクト,指定された升目と色が不正であった場合はSquare::isNullObjectがtrue
        Square putDisk(const short squareRowNo, const short squareColNo, const Disk d);
        // 指定された色の石が置ける升のリストを返す
        std::vector<Square> getValidSquareList(const Disk d) const;
        // 引数のSquareの状態で新たに石が置かれたとみなし,その結果として裏返される石の数を返す
        short tryReverse(const Square s) const;
        // 引数のSquareの状態で新たに石が置かれたとみなし,その結果として他の石を裏返し,裏返した数を返す
        short reverse(const Square s);
        // 両者共に石を置ける升が無くなった場合にtrueを返す.
        bool isEndOfMatch() const;
        // プレイヤーの石の数を返す
        short playerScore() const;
        // 対戦相手の石の数を返す
        short opponentScore() const;

        // ディスプレイへの参照
        Display &display_;
        // オセロのボード
        OthelloBoard board_;
        // プレイヤーの石の色
        Disk playerDisk_;
        // 対戦相手の石の色
        Disk opponentDisk_;
        // プレイヤーのターンの場合にtrue
        bool playerTurn_;
        // コンソール上の入力開始位置
        short startX_, startY_;
    };

} // namespace IrukakunOthello

#endif // IRUKAKUN_OTHELLO_OthelloGame_INCLUDED
