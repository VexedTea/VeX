#ifndef __VERLET_OBJECT_HPP__
#define __VERLET_OBJECT_HPP__

#include <SFML/Graphics.hpp>
#include "../utilities.hpp"

namespace VeX{

    struct Verlet_Object{
        sf::Vector2f pos;
        sf::Vector2f prevPos;
        sf::Vector2f acceleration = {0.f, 0.f};
        float radius = 10.f;
        sf::Color color = sf::Color::White;

        Verlet_Object(const sf::Vector2f & position, float radius):
            pos{position},
            radius{radius}
        {}

        void update(float dt){
            const sf::Vector2f velocity = pos - prevPos;
            prevPos = pos;
            pos = pos + velocity + acceleration * (dt * dt);
            acceleration = {};
        }

        void accelerate(const sf::Vector2f & accel){
            acceleration += accel;
        }

        void setVelocity(const sf::Vector2f & v, float dt){
            prevPos = pos - (v * dt);
        }

        void addVelocity(const sf::Vector2f & v, float dt){
            prevPos -= v * dt;
        }

        [[nodiscard]]
        sf::Vector2f getVelocity(float dt) const {
            return (pos - prevPos) / dt;
        }

        inline bool operator==(const Verlet_Object & right){
            return this->pos == right.pos and this->prevPos == right.prevPos;
        }

        inline bool operator!=(const Verlet_Object & right){
            return this->pos != right.pos or this->prevPos != right.prevPos;
        }

        inline bool friend operator==(const Verlet_Object left, const Verlet_Object right){
            return left.pos == right.pos and left.prevPos == right.prevPos;
        }
    };


} // namespace VeX

#endif // __VERLET_OBJECT_HPP__
