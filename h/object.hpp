#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <cmath>

#include "SFML/Graphics.hpp"
#include "engine.hpp"

namespace VeX{
    
    class Object{
    protected:
        sf::Vector2f position;
        sf::Vector2f velocity;
        float mass;
        sf::Vector2f motionDampening;
    public:
        Object(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            position(position),
            velocity(velocity),
            mass(mass),
            motionDampening(motionDampening)
        {}

        Object(const sf::Vector2f & position):
            Object(position, {0,0}, 0.f, {0,0})
        {}

        Object(const sf::Vector2f & position, const sf::Vector2f & velocity):
            Object(position, velocity, 0.f, {0,0})
        {}

        Object(const sf::Vector2f & position, float mass):
            Object(position, {0,0}, mass, {0,0})
        {}

        virtual void update(float delta){
            velocity = velocity / ((motionDampening * delta)+1);
            position += velocity * delta;
        }

        void gravTo(const sf::Vector2f & targetPos, float delta){
            if(targetPos == position){return;}
            float magnitude = sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
            sf::Vector2f direction = (targetPos - position)/magnitude;
            float v = -0.4*magnitude + (Definition::gravitationalConstant * delta * pow(magnitude, 1.2)) + 3;
            velocity += direction * v;
        }

        void setPosition(const sf::Vector2f & newPos){
            position = newPos;
        }

        void setPosition(const sf::Vector2i & newPos){
            setPosition(sf::Vector2f{static_cast<float>(newPos.x), static_cast<float>(newPos.y)});
        }

        sf::Vector2f getPosition(){
            return position;
        }

        void move(const sf::Vector2f & move){
            position += move;
        }

        void setVelocity(const sf::Vector2f & newVel){
            velocity = newVel;
        }

        void addVelocity(const sf::Vector2f & velAdd){
            velocity += velAdd;
        }

        sf::Vector2f getVelocity(){
            return velocity;
        }
        
    };

} // namespace VeX


#endif // __OBJECT_HPP__
