#ifndef __SPEED_GRADIENT_PARTICLE_HPP__
#define __SPEED_GRADIENT_PARTICLE_HPP__

#include "particle.hpp"

namespace VeX{

    class Speed_Gradient_Particle : public Particle{
    private:
        Color_Gradient gradient;
        float gradientEndSpeed;
    public:
        Speed_Gradient_Particle(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, 
                                const sf::Vector2f & motionDampening, const Color_Gradient & gradient, float gradientEndSpeed=1000.f):
            Particle(position, engine->makeRectangleTexture("1x1White", {1,1}, sf::Color::White), velocity, mass, motionDampening),
            gradient(gradient),
            gradientEndSpeed(gradientEndSpeed)
        {}

        Speed_Gradient_Particle(const sf::Vector2f & position, const Color_Gradient & gradient, float gradientEndSpeed=1000.f):
            Speed_Gradient_Particle(position, {0,0}, 0.f, {0,0}, gradient, gradientEndSpeed)
        {}

        Speed_Gradient_Particle(const sf::Vector2f & position, const sf::Vector2f & motionDampening, const Color_Gradient & gradient, float gradientEndSpeed=1000.f):
            Speed_Gradient_Particle(position, {0,0}, 0.f, motionDampening, gradient, gradientEndSpeed)
        {}

        virtual void update(float delta){
            velocity = velocity / ((motionDampening * delta)+1);
            position += velocity * delta;
        }

        virtual void draw(float){
            sprite.setColor(gradient.getColorAt(sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) / gradientEndSpeed));
            sprite.setPosition(position);
            engine->window.draw(sprite);
        }
    };

} // namespace VeX

#endif // __SPEED_GRADIENT_PARTICLE_HPP__
