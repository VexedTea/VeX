#ifndef __PARTICLE_IMAGE_HPP__
#define __PARTICLE_IMAGE_HPP__

#include <functional>

#include "particle_system.hpp"

namespace VeX{
    
    class Particle_Image : public Particle_System{
    private:
        sf::Texture texture;
        unsigned int maxParticleCount;
        float scale;
        std::vector<sf::Vector2f> offsets;
        unsigned int particleIndex;
        
        std::function<void(unsigned int, float)> movementFunction = [](unsigned int, float){};
    public:
        Particle_Image(const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Texture & texture, unsigned int maxParticleCount, float mass, const sf::Vector2f & motionDampening):
            Particle_System(position, velocity, mass, motionDampening),
            texture(texture),
            maxParticleCount(maxParticleCount),
            scale(1.f),
            offsets(),
            particleIndex(0)
        {
            setParticles();
        }

        Particle_Image(const sf::Texture & texture, unsigned int maxParticleCount, const sf::Vector2f & motionDampening):
            Particle_Image({0.f,0.f}, {0.f,0.f}, texture, maxParticleCount, 0.f, motionDampening)
        {}

        virtual void update(float delta)override{
            
            for(unsigned int i=0; i<particles.size(); i++){
                movementFunction(particleIndex, delta);
                particles[i]->update(delta);
                // particleIndex++;
                // if(particleIndex >= particles.size()){particleIndex=0;}
            }
        }

        void setParticles(){
            particles.clear();
            offsets.clear();
            sf::Vector2u textureSize = texture.getSize();
            sf::Vector2u patchSize = {1,1};
            if(textureSize.x * textureSize.y > maxParticleCount){
                patchSize = patchSize * int(sqrt(textureSize.x * textureSize.y / maxParticleCount)+1);
            }
            //std::cout << patchSize<<"\n";
            for(unsigned int i=0; i<textureSize.x; i+=patchSize.x){
                for(unsigned int j=0; j<textureSize.y; j+=patchSize.y){
                    std::unique_ptr<Particle> particle = std::make_unique<Particle>( 
                        sf::Vector2f(i,j)-sf::Vector2f(patchSize.x/2, patchSize.y/2),//CHANGE THIS!!! 
                        texture, motionDampening
                    );
                    offsets.push_back(sf::Vector2f(i,j)-sf::Vector2f(patchSize.x/2, patchSize.y/2));
                    particle->setTextureRect(sf::IntRect(i, j, patchSize.x, patchSize.y));
                    //std::cout << i-patchSize.x << " " << j-patchSize.y << " " << patchSize.x << " " << patchSize.y << std::endl;
                    //std::cout << "addParticle" << std::endl;
                    addParticle(std::move(particle));
                }
            }
        }

        void setSize(const sf::Vector2f & newSize){
            sf::Vector2u textureSize = texture.getSize();
            float scaleX = newSize.x / textureSize.x;
            float scaleY = newSize.y / textureSize.y;
            if(scaleX > scaleY){
                scale = scaleY;
            }else{
                scale = scaleX;
            }
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->setScale({scale, scale});
                particles[i]->setPosition(particles[i]->getPosition()*scale);
            }
        }

        void setCenterPosition(const sf::Vector2f & newPos){
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->setPosition(particles[i]->getPosition()-position+(newPos-(texture.getSize()*scale/2.f)));
            }
            position = newPos-(texture.getSize()*scale/2.f);
        }

        void collapseTo(const sf::Vector2f & newPos){
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->setVelocity({0.f,0.f});
                particles[i]->unpause();
                particles[i]->launchTo(newPos);
            }
            movementFunction = [this, newPos](unsigned int index, float ){
                //particles[index]->gravTo(newPos, delta);
                if(particles[index]->isAt(newPos, 75.f)){
                    particles[index]->pause();
                    particles[index]->hide();
                }
            };
        }

        void comeInFrom(const sf::Vector2f & fromPos){
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->setPosition(fromPos);
                particles[i]->unpause();
                particles[i]->launchTo(position + (offsets[i] * scale));
            }
            movementFunction = [this, fromPos](unsigned int index, float ){
                //particles[index]->gravTo(position + (offsets[index] * scale), delta);
                if(particles[index]->isAt(position + (offsets[index] * scale), 5.f)){
                    particles[index]->setPosition(position + (offsets[index] * scale));
                    particles[index]->pause();
                    //std::cout << index << std::endl;
                }
            };
        }

        void stop(){
            movementFunction = [](unsigned int, float){};
        }
    };

} // namespace VeX


    

#endif // __PARTICLE_IMAGE_HPP__