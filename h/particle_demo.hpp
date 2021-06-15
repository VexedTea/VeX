#ifndef __PARTICLE_DEMO_HPP__
#define __PARTICLE_DEMO_HPP__

#include <vector>
#include <memory>

#include "particle_system.hpp"
#include "engine.hpp"

namespace VeX{

    class Particle_Demo : public State{
    private:
        std::unique_ptr<Particle_System> particleSystem;
    public:
        Particle_Demo():
            particleSystem(std::make_unique<Particle_System>())
        {}

        void init(){
            engine->makeRectangleTexture("defaultParticle", {1,1}, sf::Color::White);
            particleSystem->setPosition(sf::Vector2f(engine->settings->screenWidth/2, engine->settings->screenHeight/2));
            for(unsigned int i=0; i<engine->settings->maxParticleCount; i++){
                particleSystem->addParticle(std::make_unique<Particle>(particleSystem->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                        -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, engine->getTexture("defaultParticle"), Definition::defaultParticleMotionDampening));
                engine->settings->currentParticleCount++;
            }
        }

        void handleInput(){
            sf::Event event;
            while (engine->window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    engine->window.close();
            }
        }

        void update(float delta){
            particleSystem->setPosition(sf::Mouse::getPosition(engine->window));
            particleSystem->update(delta);
        }

        void draw(float delta){
            engine->window.clear();

            particleSystem->draw(delta);

            engine->window.display();
        }
    };

} // namespace VeX

#endif // __PARTICLE_DEMO_HPP__
