#ifndef DATA_HPP
#define DATA_HPP

#include <SFML/Graphics.hpp>

namespace WINDOW
{
    const int width = 1024;
    const int height = 768;
    const std::string title = "Cat";
    const int style = sf::Style::Resize + sf::Style::Close;
}

namespace CAMERA
{
    const sf::FloatRect view_rect(0, 0, 300, 225);
}

namespace BACKGROUND
{
    const std::string img_fp = "res/sky_background.png";
}


#endif // DATA_HPP
