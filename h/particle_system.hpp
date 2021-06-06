#ifndef __PARTICLE_SYSTEM_HPP__
#define __PARTICLE_SYSTEM_HPP__

#include <memory>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "particle.hpp"

namespace VeX{

    class ParticleSystem{
    private:
        Engine & engine;
        unsigned int maxParticleCount;
        sf::Vector2f position;

        std::vector<std::unique_ptr<Particle>> particles;
    public:
        ParticleSystem(Engine & engine, const unsigned int & maxParticleCount=Definition::defaultMaxParticleCount):
            engine(engine),
            maxParticleCount{maxParticleCount},
            position{sf::Vector2f(0,0)}
        {}

        void update(const float & delta){
            sf::Vector2i mousePos = sf::Mouse::getPosition(engine.window);
            position = {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)};

            if(particles.size() < maxParticleCount){
                //for(unsigned int i=particles.size(); i<maxParticleCount; i++)//Spawn all remaining particles at once
                particles.push_back(std::make_unique<Particle>(engine, position));
                //std::cout << "New particle made as: " << position.x << " " << position.y << "\n";
            }

            //Do particle movement/physics shit here
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->gravTo(position, delta);
                particles[i]->update(delta);
                if(particles[i]->deleteMe){particles.erase(particles.begin()+i);}
            }
        }

        void draw(const float & delta){
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->draw(delta);
            }
            //std::cout << particles.size() << "\r";
        }

        void setPosition(const sf::Vector2f & newPos){
            position = newPos;
        }

        sf::Vector2f getPosition(){
            return position;
        }
    };

}
#endif // __PARTICLE_SYSTEM_HPP__
