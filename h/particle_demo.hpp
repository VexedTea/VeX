#ifndef __PARTICLE_DEMO_HPP__
#define __PARTICLE_DEMO_HPP__

#include <vector>
#include <memory>

#include "speed_gradient_particle.hpp"
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
            engine->addKeybind("resetState", sf::Keyboard::Key::Backspace);
            particleSystem->setPosition(sf::Vector2f(engine->settings->screenWidth/2, engine->settings->screenHeight/2));
            for(unsigned int i=0; i<engine->settings->maxParticleCount; i++){
                particleSystem->addParticle(std::make_unique<Speed_Gradient_Particle>(particleSystem->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                        -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                        Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                engine->settings->currentParticleCount++;
            }
        }

        void handleInput(){
            if(engine->getKeybind("resetState")->onKeyDown()){
                engine->addState(std::make_unique<VeX::Particle_Demo>(), true);
            }

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
