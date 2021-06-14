#ifndef __OLD_PARTICLE_SYSTEM_HPP__
#define __OLD_PARTICLE_SYSTEM_HPP__

#include <memory>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "old_particle.hpp"

namespace VeX{

    class Old_Particle_System{
    private:
        Engine_Ptr engine;
        sf::Color color;
        Color_Gradient colors;
        std::string textureName;
        unsigned int maxParticleCount;
        sf::Vector2f position;
        bool usingGradient;

        std::vector<std::unique_ptr<Old_Particle>> particles;
    public:
        Old_Particle_System(Engine_Ptr engine, const sf::Color & color=sf::Color::White, 
                        const std::string & textureName="defaultParticle", 
                        const unsigned int & maxParticleCount=Definition::defaultMaxParticleCount):
            engine(engine),
            color(color),
            colors({color}),
            textureName(textureName),
            maxParticleCount{maxParticleCount},
            position{sf::Vector2f(0,0)},
            usingGradient(false)
        {}

        Old_Particle_System(Engine_Ptr engine, const Color_Gradient & colors, 
                        const std::string & textureName="defaultParticle", 
                        const unsigned int & maxParticleCount=Definition::defaultMaxParticleCount):
            engine(engine),
            color(sf::Color::White),
            colors(colors),
            textureName(textureName),
            maxParticleCount{maxParticleCount},
            position{sf::Vector2f(0,0)},
            usingGradient(true)
        {}

        Old_Particle_System(Engine_Ptr engine, const unsigned int & maxParticleCount, const sf::Vector2f & position={0,0}):
            engine(engine),
            color(sf::Color::White),
            colors({color}),
            textureName("defaultParticle"),
            maxParticleCount{maxParticleCount},
            position{position},
            usingGradient(false)
        {}

        virtual void update(const float & delta){

            if(particles.size() < maxParticleCount){
                for(unsigned int i=particles.size(); i<maxParticleCount; i++)//Spawn all remaining particles at once
                particles.push_back(std::make_unique<Old_Particle>(engine, position, color, colors, usingGradient, textureName, sf::Vector2f{1,1}, 1.f));
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

        void applyForceToAll(const sf::Vector2f & force){
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->applyForce(force);
            }
        }

        void setPosition(const sf::Vector2f & newPos){
            position = newPos;
        }

        void setPosition(const sf::Vector2i & newPos){
            setPosition(sf::Vector2f{static_cast<float>(newPos.x), static_cast<float>(newPos.y)});
        }

        sf::Vector2f getPosition(){
            return position;
        }

        void move(const sf::Vector2f & movement){
            position += movement;
        }

        void addParticle(const sf::Vector2f & _position, const sf::Color & color, const std::string & textureName, const sf::Vector2f & scale={1,1}, const float & mass=1.f){
            particles.push_back(std::make_unique<Old_Particle>(engine, _position+position, color, Color_Gradient{{sf::Color::White}}, false, textureName, scale, mass));
        }

        void addParticle(std::unique_ptr<Old_Particle> particle){
            particle->move(position);
            particles.push_back(std::move(particle));
        }
    };

}

#endif // __OLD_PARTICLE_SYSTEM_HPP__
