#include "../h/transform_util.hpp"

namespace VeX{

    sf::Sprite snapTo(sf::Sprite sprite, sf::Vector2f pos, sf::Vector2f scale){
        sprite.setOrigin(sprite.getTexture()->getSize()/2.f);
        sprite.setScale((engine->settings->getScreenSize()/sprite.getTexture()->getSize())*scale);
        sprite.setPosition(pos*engine->settings->getScreenSize());
        return sprite;
    }

    sf::Sprite snapTo(sf::Sprite sprite, float xPos, float yPos, sf::Vector2f scale){
        return snapTo(sprite, {xPos, yPos}, scale);
    }

    sf::Sprite snapTo(sf::Sprite sprite, sf::Vector2f pos, float xScale, float yScale){
        return snapTo(sprite, pos, {xScale, yScale});
    }

    sf::Sprite snapTo(sf::Sprite sprite, float xPos, float yPos, float xScale, float yScale){
        return snapTo(sprite, {xPos, yPos}, {xScale, yScale});
    }

} // namespace VeX
