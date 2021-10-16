#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

#include "object.hpp"
#include "color_gradient.hpp"

namespace VeX{

    class Particle : public Object{
    private:
        Color_Gradient gradient;
        float gradientEndSpeed;
    public:
        Particle(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening,
                        const Color_Gradient & gradient, float gradientEndSpeed=1000.f);

        Particle(const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & motionDampening,
                        const Color_Gradient & gradient, float gradientEndSpeed=1000.f);

        Particle(const sf::Vector2f & position, const sf::Vector2f & velocity,
                        const Color_Gradient & gradient, float gradientEndSpeed=1000.f);

        Particle(const sf::Vector2f & position, const Color_Gradient & gradient, float gradientEndSpeed=1000.f);
        sf::Color getColor();
    };

    using Particle_Ptr = std::unique_ptr<Particle>;

} // namespace VeX

#endif // __PARTICLE_HPP__
