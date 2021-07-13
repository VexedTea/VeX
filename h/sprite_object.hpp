#ifndef __SPRITE_OBJECT_HPP__
#define __SPRITE_OBJECT_HPP__

#include "object.hpp"
#include "engine.hpp"

namespace VeX{

    class Sprite_Object : public Object{
    protected:
        sf::Sprite sprite;
    public:
        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            Object(position, velocity, mass, motionDampening),
            sprite(texture)
        {
            sprite.setPosition(position);
        }

        Sprite_Object(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            Object(position, velocity, mass, motionDampening),
            sprite()
        {
            sprite.setPosition(position);
        }

        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity, const sf::Vector2f & motionDampening):
            Sprite_Object(position, texture, velocity, 0.f, motionDampening)
        {}

        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & velocity):
            Sprite_Object(position, texture, velocity, 0.f, {0,0})
        {}

        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture, float mass):
            Sprite_Object(position, texture, {0,0}, mass, {0,0})
        {}

        Sprite_Object(const sf::Vector2f & position, const sf::Texture & texture):
            Sprite_Object(position, texture, {0,0}, 0.f, {0,0})
        {}

        virtual void draw(float)override{
            if(!hidden){
                sprite.setPosition(position);
                engine->window.draw(sprite);
            }
        }

        void setTexture(const sf::Texture & texture, const sf::IntRect & textureRect={0,0,0,0}){
            sprite.setTexture(texture);
            if(textureRect != sf::IntRect{0,0,0,0}){
                sprite.setTextureRect(textureRect);
            }
        }

        void setTextureRect(const sf::IntRect & rect){
            sprite.setTextureRect(rect);
        }

        sf::IntRect getTextureRect(){
            return sprite.getTextureRect();
        }

        void setScale(const sf::Vector2f & newScale){
            sprite.setScale(newScale);
        }

    };

} // namespace VeX

#endif // __SPRITE_OBJECT_HPP__
