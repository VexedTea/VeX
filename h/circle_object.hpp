#ifndef __CIRCLE_OBJECT_HPP__
#define __CIRCLE_OBJECT_HPP__

#include "object.hpp"

namespace VeX{

    class Circle_Object : public Object{
    private:
        float size;
        sf::CircleShape body;
    public:
        Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            Object(position, velocity, mass, motionDampening),
            size(size),
            body(size)
        {
            body.setPosition(position);
            body.setFillColor(color);
            body.setOrigin({size, size});
        }

        Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, float mass, const sf::Vector2f & velocity):
            Circle_Object(position, size, color, velocity, mass, {0,0})
        {}

        Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, float mass):
            Circle_Object(position, size, color, {0,0}, mass, {0,0})
        {}

        Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color):
            Circle_Object(position, size, color, {0,0}, 0.f, {0,0})
        {}

        virtual void draw(float)override{
            body.setPosition(position);
            engine->window.draw(body);
        }

        bool collidesWith(const sf::Vector2f & otherPos, float otherSize){
            return distance(position, otherPos) < size + otherSize;
        }

        float getSize(){
            return size;
        }

        void setSize(float newSize){
            size = newSize;
            body.setRadius(size);
            body.setOrigin({size, size});
        }
    };

} // namespace VeX

#endif // __CIRCLE_OBJECT_HPP__
