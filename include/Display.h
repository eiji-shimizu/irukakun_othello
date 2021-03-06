#ifndef IRUKAKUN_OTHELLO_Display_INCLUDED
#define IRUKAKUN_OTHELLO_Display_INCLUDED

#include <array>
#include <string>
#include <utility>

namespace IrukakunOthello
{
    /*
    画面クラス
    10×10の2次元配列を持ち,その要素がコンソールに表示される.
    要素にはutf-8の半角2文字かutf-8の全角1文字を表示文字として入れる.
    */
    class Display
    {
    public:
        static const std::string FULL_WIDTH_SPACE;
        static const std::string CRLF;
        static const std::string FULL_WIDTH_DOT;
        static const std::string BLACK_DISK;
        static const std::string WHITE_DISK;
        static const std::string ONE;
        static const std::string TWO;
        static const std::string THREE;
        static const std::string FOUR;
        static const std::string FIVE;
        static const std::string SIX;
        static const std::string SEVEN;
        static const std::string EIGHT;

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
        // 引数の座標を内に含む要素の添え字を返す
        std::pair<int, int> convertToElementIndex(const short x, const short y) const;

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
            short x() const;
            short y() const;
            void draw() const;
            std::string toString() const;

        private:
            // 表示文字
            std::string letter_;
            // コンソール上の表示位置
            short x_, y_;
        };

        static const int xUpperLimit = 10;
        static const int yUpperLimit = 10;
        // 表示文字の2次元配列
        std::array<std::array<Element, yUpperLimit>, xUpperLimit> data_;
    };

} // namespace IrukakunOthello

#endif // IRUKAKUN_OTHELLO_Display_INCLUDED
