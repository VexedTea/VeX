#ifndef __PARTICLE_SYSTEM_FACTORY_HPP__
#define __PARTICLE_SYSTEM_FACTORY_HPP__

#include <memory>

#include "particle_system.hpp"

namespace VeX{
    
    using Particle_System_Ptr = std::unique_ptr<Particle_System>;

    class Particle_System_Factory{
    public:
        static Particle_System_Ptr makePixelSizedParticleSystem(Engine & engine,  const sf::Color & color, 
                                                                const unsigned int & maxParticleCount=Definition::defaultMaxParticleCount){
            engine.makeRectangleTexture("1x1White", {1, 1}, sf::Color::White);
            return std::make_unique<Particle_System>(engine, color, "1x1White", maxParticleCount);
        }

        static Particle_System_Ptr makePixelSizedParticleSystem(Engine & engine,  const Color_Gradient & colors, 
                                                                const unsigned int & maxParticleCount=Definition::defaultMaxParticleCount){
            engine.makeRectangleTexture("1x1White", {1, 1}, sf::Color::White);
            return std::make_unique<Particle_System>(engine, colors, "1x1White", maxParticleCount);
        }
    };

} // namespace VeX


#endif // __PARTICLE_SYSTEM_FACTORY_HPP__
