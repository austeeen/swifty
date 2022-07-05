#ifndef DATA_HPP
#define DATA_HPP

#include <SFML/Graphics.hpp>

namespace WINDOW
{
    const int width = 1024;
    const int height = 768;
    const std::string title = "Swifty";
    const int style = sf::Style::Resize + sf::Style::Close;
}

namespace CAMERA
{
    const sf::FloatRect view_rect(0, 0, 300, 225);
}


#endif // DATA_HPP
