#include "../h/particle.hpp"

namespace VeX{

    Particle::Particle(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening,
                    const Color_Gradient & gradient, float gradientEndSpeed):
        Object(position, velocity, mass, motionDampening),
        gradient(gradient),
        gradientEndSpeed(gradientEndSpeed)
    {}

    Particle::Particle(const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & motionDampening,
                    const Color_Gradient & gradient, float gradientEndSpeed):
        Particle(position, velocity, 0.f, motionDampening, gradient, gradientEndSpeed)
    {}

    Particle::Particle(const sf::Vector2f & position, const sf::Vector2f & velocity,
                    const Color_Gradient & gradient, float gradientEndSpeed):
        Particle(position, velocity, 0.f, Definition::defaultParticleMotionDampening, gradient, gradientEndSpeed)
    {}

    Particle::Particle(const sf::Vector2f & position, const Color_Gradient & gradient, float gradientEndSpeed):
        Particle(position, {0.f, 0.f}, 0.f, Definition::defaultParticleMotionDampening, gradient, gradientEndSpeed)
    {}

    sf::Color Particle::getColor(){
        return gradient.getColorAt(sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) / gradientEndSpeed);
    }

} // namespace VeX
