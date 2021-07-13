#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <cmath>

#include "SFML/Graphics.hpp"
#include "engine.hpp"

namespace VeX{
    
    class Object{
    protected:
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Vector2f velocity;
        float mass;
        sf::Vector2f motionDampening;

        bool paused;
        bool hidden;
    public:
        Object(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            position(position),
            size(size),
            velocity(velocity),
            mass(mass),
            motionDampening(motionDampening),
            paused(false),
            hidden(false)
        {}

        Object(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            Object(position, {0.f,0.f}, velocity, mass, motionDampening)
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
            if(!paused){
                velocity = velocity / ((motionDampening * delta)+1);
                position += velocity * delta;
            }
        }

        void gravTo(const sf::Vector2f & targetPos, float delta){
            if(!paused){
                if(targetPos == position){return;}
                float magnitude = sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
                sf::Vector2f direction = (targetPos - position)/magnitude;
                float v = -0.4*magnitude + (engine->settings->gravity * delta * pow(magnitude, 1.2)) + 3;
                velocity += direction * v;
            }
        }

        void launchTo(const sf::Vector2f & targetPos){
            float distance = sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
            sf::Vector2f direction = (targetPos - position)/distance;
            float v = distance * motionDampening.x; //Change this
            velocity += (direction * v);
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
        
        void pause(){
            paused = true;
        }

        void unpause(){
            paused = false;
        }

        virtual void hide(){
            hidden = true;
        }

        void unhide(){
            hidden = false;
        }

        bool isAt(const sf::Vector2f & targetPos, float range=1.f){
            return range > sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
        }
    };

} // namespace VeX


#endif // __OBJECT_HPP__
