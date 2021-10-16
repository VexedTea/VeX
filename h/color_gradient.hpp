#ifndef __COLOR_GRADIENT_HPP__
#define __COLOR_GRADIENT_HPP__

#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"

namespace VeX{
    
    class Color_Gradient{
    private:
        std::vector<sf::Color> colors;
    public:
        Color_Gradient(const std::vector<sf::Color> & colors);

        Color_Gradient();

        sf::Color getColorAt(float fraction, bool debug=false)const;

        sf::Color getFirst();
    };

} // namespace VeX


#endif // __COLOR_GRADIENT_HPP__
