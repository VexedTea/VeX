#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include "SFML/Graphics.hpp"

namespace VeX{
    
    class Object{
    private:
        sf::Vector2f position;
        sf::Vector2f velocity;
    public:
        Object(const sf::Vector2f & position, const sf::Vector2f & velocity={0,0}):
            position(position),
            velocity(velocity)
        {}

        virtual void update(float delta){
            position += velocity * delta;
        }

        void setPosition(const sf::Vector2f & newPos){
            position = newPos;
        }
    };

} // namespace VeX


#endif // __OBJECT_HPP__
