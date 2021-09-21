#ifndef __VERTEX_PARTICLE_HPP__
#define __VERTEX_PARTICLE_HPP__

#include "object.hpp"
#include "color_gradient.hpp"

namespace VeX{

    class Vertex_Particle : public Object{
    private:
        Color_Gradient gradient;
        float gradientEndSpeed;
    public:
        Vertex_Particle(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening,
                        const Color_Gradient & gradient, float gradientEndSpeed=1000.f):
            Object(position, velocity, mass, motionDampening),
            gradient(gradient),
            gradientEndSpeed(gradientEndSpeed)
        {}

        Vertex_Particle(const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & motionDampening,
                        const Color_Gradient & gradient, float gradientEndSpeed=1000.f):
            Vertex_Particle(position, velocity, 0.f, motionDampening, gradient, gradientEndSpeed)
        {}

        Vertex_Particle(const sf::Vector2f & position, const sf::Vector2f & velocity,
                        const Color_Gradient & gradient, float gradientEndSpeed=1000.f):
            Vertex_Particle(position, velocity, 0.f, Definition::defaultParticleMotionDampening, gradient, gradientEndSpeed)
        {}

        Vertex_Particle(const sf::Vector2f & position, const Color_Gradient & gradient, float gradientEndSpeed=1000.f):
            Vertex_Particle(position, {0.f, 0.f}, 0.f, Definition::defaultParticleMotionDampening, gradient, gradientEndSpeed)
        {}

        sf::Color getColor(){
            return gradient.getColorAt(sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) / gradientEndSpeed);
        }
    };

    using Vertex_Particle_Ptr = std::unique_ptr<Vertex_Particle>;

} // namespace VeX

#endif // __VERTEX_PARTICLE_HPP__
