#ifndef __COLOR_GRADIENT_HPP__
#define __COLOR_GRADIENT_HPP__

#include <vector>
#include "SFML/Graphics.hpp"

namespace VeX{
    
    class Color_Gradient{
    private:
        std::vector<sf::Color> colors;
    public:
        Color_Gradient(const std::vector<sf::Color> & colors):
            colors(colors)
        {
            if(colors.size()==0){
                std::cout << "[VeX WARNING] Color gradient instantiated on empty gradient!\n";
            }
        }

        sf::Color getColorAt(float fraction, bool debug=false)const{
            if(fraction <= 0){ //Here it's going to fully be the first color in the gradient anyways
                //std::cout << fraction << " \n";
                return colors[0];
            }else if(fraction >= 1){ //Here it's going to fully be the last color in the gradient anyways
                //std::cout << fraction << " \n";
                return colors[colors.size()-1];
            }
            if(debug)std::cout << fraction << " ";
            fraction *= colors.size()-1;
            if(debug)std::cout << fraction << " ";
            sf::Color color1 = colors[int(fraction)];
            sf::Color color2 = colors[int(fraction)+1];
            if(debug)std::cout << int(fraction) << " ";
            fraction = fraction - int(fraction);
            if(debug)std::cout << fraction << " \n";
            return sf::Color(
                            ((1-fraction) * color1.r) + (fraction * color2.r),
                            ((1-fraction) * color1.g) + (fraction * color2.g),
                            ((1-fraction) * color1.b) + (fraction * color2.b)
            );
        }

        sf::Color getFirst(){
            return colors[0];
        }
    };

} // namespace VeX


#endif // __COLOR_GRADIENT_HPP__
