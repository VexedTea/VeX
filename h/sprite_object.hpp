#ifndef __SPRITE_OBJECT_HPP__
#define __SPRITE_OBJECT_HPP__

#include "object.hpp"
#include "engine.hpp"

namespace VeX{

    class Sprite_Object : public Object{
    protected:
        sf::Sprite sprite;
    public:
        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening);

        Sprite_Object(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening);

        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity, const sf::Vector2f & motionDampening);

        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity);

        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, float mass);

        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture);

        virtual void draw(float)override;

        void setTexture(const sf::Texture & texture, const sf::IntRect & textureRect={0,0,0,0});

        void setTextureRect(const sf::IntRect & rect);

        sf::IntRect getTextureRect();

        void setScale(const sf::Vector2f & newScale);

    };

} // namespace VeX

#endif // __SPRITE_OBJECT_HPP__
