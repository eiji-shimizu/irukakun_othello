#ifndef IRUKAKUN_OTHELLO_OthelloGame_INCLUDED
#define IRUKAKUN_OTHELLO_OthelloGame_INCLUDED

namespace IrukakunOthello
{
    enum Color
    {
        BLACK,
        WHITE,
        RED // assert確認用,後に消す
    };

    class Display;

    class OthelloGame
    {
    public:
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
        // 指定された升目にプレイヤーの色の石を設定する.
        // 升目は左上から順に(行,列)で(1,1)(1,2) ... (1,8)
        // (8,1)(8,2)...(8,8)と右下に向かって指定する.
        void putDisk(const short squareRowNo, const short squareColNo);
        // 第3引数で指定された色の石を指定された升目に設定する
        void putDisk(const short squareRowNo, const short squareColNo, const Color c);
        // 指定された升目の内容を再描画する
        void reDraw(const short squareRowNo, const short squareColNo);

    private:
        // ディスプレイへの参照
        Display &display_;
        // プレイヤーの石の色
        Color playerColor_;
        // コンソール上の入力開始位置
        short startX_, startY_;
    };

} // namespace IrukakunOthello

#endif // IRUKAKUN_OTHELLO_OthelloGame_INCLUDED
