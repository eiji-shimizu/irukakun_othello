#include "Display.h"

#include <sstream>
#include <iostream>

namespace IrukakunOthello
{
    const std::string FULL_WIDTH_SPACE = "　";
    const std::string FULL_WIDTH_DOT = "・";
    const std::string BLACK_STONE = "●";
    const std::string WHITE_STONE = "○";

    Display::Element::Element(std::string letter)
        : letter_(letter)
    {
    }

    Display::Element::Element()
        : letter_(FULL_WIDTH_SPACE)
    {
    }

    Display::Element::~Element()
    {
        // noop
    }

    void Display::Element::setLetter(std::string letter)
    {
        letter_ = letter;
    }

    std::string Display::Element::toString() const
    {
        return letter_;
    }

    Display::Display()
    {
        // noop
    }

    Display::~Display()
    {
        // noop
    }

    void Display::setLetter(std::size_t rowNo, std::size_t colNo, std::string letter)
    {
        data_[rowNo][colNo].setLetter(letter);
    }

    std::string Display::toString() const
    {
        std::ostringstream oss;
        for (std::size_t i = 0; i < data_.size(); i++)
        {
            for (std::size_t j = 0; j < data_[i].size(); j++)
            {
                oss << data_[i][j].toString();
            }
        }
        return oss.str();
    }

} // namespace IrukakunOthello