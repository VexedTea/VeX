#ifndef __PARTICLE_SYSTEM_FACTORY_HPP__
#define __PARTICLE_SYSTEM_FACTORY_HPP__

#include <memory>
#include <cmath>

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

        static Particle_System_Ptr makeParticleSystemFromImage(Engine & engine,  const std::string & texturePath, const unsigned int & maxParticleCount, const sf::Vector2f & position={0.f,0.f}){
            const sf::Texture & texture = engine.loadTexture(texturePath, texturePath);
            Particle_System_Ptr particleSystem = std::make_unique<Particle_System>(engine, 0, position);
            sf::Vector2u textureSize = texture.getSize();

            sf::Vector2u patchSize = {1,1};
            if(textureSize.x * textureSize.y > maxParticleCount){
                patchSize = patchSize * int(sqrt(textureSize.x * textureSize.y / maxParticleCount)+1);
            }
            //std::cout << patchSize<<"\n";

            for(unsigned int i=patchSize.x; i<textureSize.x; i+=patchSize.x){
                for(unsigned int j=patchSize.y; j<textureSize.y; j+=patchSize.y){
                    std::unique_ptr<Particle> particle = std::make_unique<Particle>(engine, 
                                                sf::Vector2f(i-patchSize.x,j-patchSize.y)-sf::Vector2f(patchSize.x/2, patchSize.y/2) - (position/2),//CHANGE THIS!!! 
                                                texturePath, sf::IntRect(i-patchSize.x, j-patchSize.y, patchSize.x, patchSize.y), 
                                                sf::Vector2f{1.f,1.f}, 1.f, sf::Vector2f{0.f,0.f}, sf::Vector2f{0.f,0.f});
                    particleSystem->addParticle(move(particle));
                }
            }
            return particleSystem;
        }
    };

} // namespace VeX


#endif // __PARTICLE_SYSTEM_FACTORY_HPP__
