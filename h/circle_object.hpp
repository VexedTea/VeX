#ifndef __CIRCLE_OBJECT_HPP__
#define __CIRCLE_OBJECT_HPP__

#include "object.hpp"

namespace VeX{

    class Circle_Object : public Object{
    private:
        float size;
        sf::CircleShape body;
    public:
        Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening);

        Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, float mass, const sf::Vector2f & velocity);

        Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, float mass);

        Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color);

        virtual void draw(float)override;

        bool collidesWith(const sf::Vector2f & otherPos, float otherSize);

        float getSize();

        void setSize(float newSize);
    };

} // namespace VeX

#endif // __CIRCLE_OBJECT_HPP__
