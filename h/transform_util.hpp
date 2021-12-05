#ifndef __TRANSFORM_UTIL_HPP__
#define __TRANSFORM_UTIL_HPP__

#include "SFML/Graphics.hpp"
#include "engine.hpp"

namespace VeX{
namespace util{

    sf::Sprite snapTo(sf::Sprite sprite, sf::Vector2f pos, sf::Vector2f scale);
    sf::Sprite snapTo(sf::Sprite sprite, float xPos, float yPos, sf::Vector2f scale);
    sf::Sprite snapTo(sf::Sprite sprite, sf::Vector2f pos, float xScale, float yScale);
    sf::Sprite snapTo(sf::Sprite sprite, float xPos, float yPos, float xScale, float yScale);

}
} // namespace VeX

#endif // __TRANSFORM_UTIL_HPP__
