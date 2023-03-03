#ifndef __VERLET_OBJECT_HPP__
#define __VERLET_OBJECT_HPP__

#include <SFML/Graphics.hpp>

namespace VeX{

    struct Verlet_Object{
        sf::Vector2f pos;
        sf::Vector2f prevPos;
        sf::Vector2f acceleration;

        void update(float dt){
            const sf::Vector2f velocity = pos - prevPos;
            prevPos = pos;
            pos = pos + velocity + acceleration * dt * dt;
            acceleration = {};
        }

        void accelerate(const sf::Vector2f & accel){
            acceleration += accel;
        }
    };

} // namespace VeX

#endif // __VERLET_OBJECT_HPP__
