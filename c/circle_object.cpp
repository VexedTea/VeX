#include "../h/circle_object.hpp"

namespace VeX{

    Circle_Object::Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
        Object(position, velocity, mass, motionDampening),
        size(size),
        body(size)
    {
        body.setPosition(position);
        body.setFillColor(color);
        body.setOrigin({size, size});
    }

    Circle_Object::Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, float mass, const sf::Vector2f & velocity):
        Circle_Object(position, size, color, velocity, mass, {0,0})
    {}

    Circle_Object::Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color, float mass):
        Circle_Object(position, size, color, {0,0}, mass, {0,0})
    {}

    Circle_Object::Circle_Object(const sf::Vector2f & position, float size, const sf::Color & color):
        Circle_Object(position, size, color, {0,0}, 0.f, {0,0})
    {}

    void Circle_Object::draw(float){
        body.setPosition(position);
        engine->window.draw(body);
    }

    bool Circle_Object::collidesWith(const sf::Vector2f & otherPos, float otherSize){
        return distance(position, otherPos) < size + otherSize;
    }

    float Circle_Object::getSize(){
        return size;
    }

    void Circle_Object::setSize(float newSize){
        size = newSize;
        body.setRadius(size);
        body.setOrigin({size, size});
    }

} // namespace VeX
