#ifndef __PARTICLE_EXPERIMENTS_HPP__
#define __PARTICLE_EXPERIMENTS_HPP__

#include "particle_system.hpp"
#include <string>

namespace VeX{

    class Particle_Experiments : public State{
    private:
        Particle_System particleSystem;
        sf::Vector2f prevMousePos;

        void addDefaultParticles(){
            engine->loadTexture("Particle", "assets/textures/particle.png");
            for(unsigned int i=0; i<engine->settings->maxParticleCount; i++){
                particleSystem.addParticle(std::make_unique<Particle>(particleSystem.getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                    -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))},
                                                                    engine->getTexture("Particle"),
                                                                    Definition::defaultParticleMotionDampening));
                engine->settings->currentParticleCount++;
            }
        }

    public:
        Particle_Experiments():
            particleSystem(),
            prevMousePos(sf::Mouse::getPosition())
        {}
        
        void init(){
            particleSystem.setPosition(sf::Vector2f(engine->settings->screenWidth/2, engine->settings->screenHeight/2));
        }
        
        void handleInput(){
            //Handle ur input
            
            sf::Event event;
            while (engine->window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                engine->window.close();
            }
        }
        
        void update(float delta){
            particleSystem.setPosition(sf::Mouse::getPosition(engine->window));
            for(unsigned int i=0; i<100; i++){
                particleSystem.addParticle(std::make_unique<Particle>(particleSystem.getPosition(), 
                                                                    (vector2iToVector2f(sf::Mouse::getPosition()) - prevMousePos) * delta * 1000.f));
                engine->settings->currentParticleCount++;
            }
            prevMousePos = vector2iToVector2f(sf::Mouse::getPosition());
            particleSystem.update(delta);
        }
        
        void draw(float delta){
            engine->window.clear();
            
            particleSystem.draw(delta);
            
            particleSystem.drawCenterPoint();
            engine->displayFramerate();
            engine->displayCurrentParticleCount();
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __PARTICLE_EXPERIMENTS_HPP__
