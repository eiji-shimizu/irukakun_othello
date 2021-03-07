#ifndef IRUKAKUN_OTHELLO_Display_INCLUDED
#define IRUKAKUN_OTHELLO_Display_INCLUDED

#include <array>
#include <string>

namespace IrukakunOthello
{

    extern const std::string FULL_WIDTH_SPACE;
    extern const std::string CRLF;
    extern const std::string FULL_WIDTH_DOT;
    extern const std::string BLACK_DISK;
    extern const std::string WHITE_DISK;
    extern const std::string ONE;
    extern const std::string TWO;
    extern const std::string THREE;
    extern const std::string FOUR;
    extern const std::string FIVE;
    extern const std::string SIX;
    extern const std::string SEVEN;
    extern const std::string EIGHT;

    /*
    画面クラス
    10×10の2次元配列を持ち,その要素がコンソールに表示される.
    要素にはutf-8の半角2文字かutf-8の全角1文字を表示文字として入れる.
    */
    class Display
    {
    public:
        Display();
        ~Display();

        // コピー禁止
        Display(const Display &) = delete;
        Display &operator=(const Display &) = delete;
        // ムーブ禁止
        Display(Display &&) = delete;
        Display &operator=(Display &&) = delete;

        // 内容を初期化した状態でコンソールに表示する
        // 添え字[i][j]に応じて初期表示したい内容を返す関数ポインタを引数にとる
        // このメソッド呼び出しにより各要素の画面上の表示位置が設定される
        void initializeDisplay(std::string (*initialValueGenerator)(const std::size_t i, const std::size_t j));
        // 指定された行列の位置の要素に第3引数の文字を設定する
        void setLetter(std::size_t rowNo, std::size_t colNo, std::string letter);
        // 指定された行列の位置の要素の内容をコンソール出力する
        void draw(std::size_t rowNo, std::size_t colNo) const;
        // 全要素をコンソール出力する
        void drawAll() const;
        // 現在のカーソル位置を引数に設定する
        void getCurrentCursorPosition(short &x, short &y) const;
        // カーソル位置を設定する
        void setCurrentCursorPosition(const short x, const short y) const;
        std::string toString() const;

    private:
        // 画面に表示する1要素のクラス
        class Element
        {
        public:
            Element(std::string letter, short x, short y);
            Element(std::string letter);
            Element();
            ~Element();

            // コピー禁止
            Element(const Element &) = delete;
            Element &operator=(const Element &) = delete;
            // ムーブ禁止
            Element(Element &&) = delete;
            Element &operator=(Element &&) = delete;

            void setLetter(std::string letter);
            void setX(short x);
            void setY(short y);
            void draw() const;
            std::string toString() const;

        private:
            // 表示文字
            std::string letter_;
            // コンソール上の表示位置
            short x_, y_;
        };

        // 表示文字の2次元配列
        std::array<std::array<Element, 10>, 10> data_;
    };

} // namespace IrukakunOthello

#endif // IRUKAKUN_OTHELLO_Display_INCLUDED
