#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

#include <memory>
#include "sprite_object.hpp"
#include "engine.hpp"

namespace VeX{

    class Particle : public Sprite_Object{
    private:
        
    public:
        Particle(const sf::Vector2f & position, const sf::Texture & texture, 
                const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            Sprite_Object(position, texture, velocity, mass, motionDampening)
        {}

        Particle(const sf::Vector2f & position, const sf::Texture & texture):
            Particle(position, texture, {0,0}, 0.f, {0,0})
        {}

        Particle(const sf::Vector2f & position, const sf::Texture & texture, const sf::Vector2f & motionDampening):
            Particle(position, texture, {0,0}, 0.f, motionDampening)
        {}
    };

    using Particle_Ptr = std::unique_ptr<Particle>;

} // namespace VeX

#endif // __PARTICLE_HPP__
