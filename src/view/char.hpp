#ifndef __VIEW_CHAR__
#define __VIEW_CHAR__

#include <stdint.h>
#include <ftxui/dom/canvas.hpp>

#define CHAR_SIZE 24

namespace view
{

extern const uint8_t charMap[53][CHAR_SIZE * CHAR_SIZE / 16];

class CharCanvas: public ftxui::Canvas
{
public:
    CharCanvas(uint16_t width, uint16_t height)
        : ftxui::Canvas(width, height)
    {
    }
    void DrawChar(uint16_t x, uint16_t y, char c, ftxui::Color color)
    {
        int8_t offset = -'a' + 26;
        if (c < 'a' || c > 'z')
        {
            if (c < 'A' || c > 'Z')
            {
                return;
            }
            offset = -'A';
        }
        uint8_t index = c + offset;
        for (uint8_t i = 0; i < CHAR_SIZE / 2; i++)
        {
            for (uint8_t j = 0; j < CHAR_SIZE / 8; j++)
            {
                uint8_t data = charMap[index][i * (CHAR_SIZE / 8) + j];
                for (uint8_t k = 0; k < 8; k++)
                {
                    DrawPoint(x + i, y + j * 8 + k, data & 1, color);
                    data >>= 1;
                }
            }
        }
    }

    void DrawString(uint16_t x, uint16_t y, const std::string& str, ftxui::Color color)
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            DrawChar(x + i * (CHAR_SIZE / 2), y, str[i], color);
        }
    }

    void Clear()
    {
        auto w = this->width();
        auto h = this->height();
        for (uint16_t i = 0; i < w; i++)
        {
            for (uint16_t j = 0; j < h; j++)
            {
                DrawPoint(i, j, false, ftxui::Color::Default);
            }
        }
    }
};


} // namespac




#endif