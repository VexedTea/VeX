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
        sf::Vector2f previousPosition;
    public:
        Object(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening);

        Object(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening);

        Object(const sf::Vector2f & position);

        Object(const sf::Vector2f & position, const sf::Vector2f & velocity);

        Object(const sf::Vector2f & position, float mass);

        virtual void update(float delta);

        virtual void draw(float);

        void gravTo(const sf::Vector2f & targetPos, float delta);

        void launchTo(const sf::Vector2f & targetPos);

        void setPosition(const sf::Vector2f & newPos);

        void setPosition(const sf::Vector2i & newPos);

        sf::Vector2f getPosition();

        void move(const sf::Vector2f & move);

        void setVelocity(const sf::Vector2f & newVel);

        void addVelocity(const sf::Vector2f & velAdd);

        sf::Vector2f getVelocity();

        float getMass();

        void addMass(float massAdd);
        
        void pause();

        void unpause();

        virtual void hide();

        void unhide();

        bool isAt(const sf::Vector2f & targetPos, float range=1.f);

        void goBack();
    };

} // namespace VeX


#endif // __OBJECT_HPP__
