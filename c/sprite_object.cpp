#include "../h/sprite_object.hpp"

namespace VeX{

    Sprite_Object::Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
        Object(position, velocity, mass, motionDampening),
        sprite(texture)
    {
        sprite.setPosition(position);
    }

    Sprite_Object::Sprite_Object(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
        Object(position, velocity, mass, motionDampening),
        sprite()
    {
        sprite.setPosition(position);
    }

    Sprite_Object::Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity, const sf::Vector2f & motionDampening):
        Sprite_Object(position, texture, velocity, 0.f, motionDampening)
    {}

    Sprite_Object::Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity):
        Sprite_Object(position, texture, velocity, 0.f, {0,0})
    {}

    Sprite_Object::Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, float mass):
        Sprite_Object(position, texture, {0,0}, mass, {0,0})
    {}

    Sprite_Object::Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture):
        Sprite_Object(position, texture, {0,0}, 0.f, {0,0})
    {}

    void Sprite_Object::draw(float){
        if(!hidden){
            sprite.setPosition(position);
            engine->window.draw(sprite);
        }
    }

    void Sprite_Object::setTexture(const sf::Texture & texture, const sf::IntRect & textureRect){
        sprite.setTexture(texture);
        if(textureRect != sf::IntRect{0,0,0,0}){
            sprite.setTextureRect(textureRect);
        }
    }

    void Sprite_Object::setTextureRect(const sf::IntRect & rect){
        sprite.setTextureRect(rect);
    }

    sf::IntRect Sprite_Object::getTextureRect(){
        return sprite.getTextureRect();
    }

    void Sprite_Object::setScale(const sf::Vector2f & newScale){
        sprite.setScale(newScale);
    }

} // namespace VeX
