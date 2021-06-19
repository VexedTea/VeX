#ifndef __MULTITHREADED_PARTICLE_DEMO_HPP__
#define __MULTITHREADED_PARTICLE_DEMO_HPP__

#include <vector>
#include <memory>
#include <thread>

#include "speed_gradient_particle.hpp"
#include "particle_system.hpp"
#include "engine.hpp"

namespace VeX{

    // This shit is kinda fucked rn, it works but the performance is *much* worse than single threading, almost certainly because i spawn and close my threads all the time, I'll have a look at how to do this better in future.

    class Multithreaded_Particle_Demo : public State{
    private:
        std::vector<std::unique_ptr<Particle_System>> particleSystems;
    public:
        Multithreaded_Particle_Demo():
            particleSystems()
        {}

        void init(){
            engine->addKeybind("resetState", sf::Keyboard::Key::Backspace);
            for(unsigned int i=0; i<2; i++){
                particleSystems.push_back(std::move(std::make_unique<Particle_System>()));
                particleSystems[i]->setPosition(sf::Vector2f(engine->settings->screenWidth/2, engine->settings->screenHeight/2));
            }
            for(unsigned int i=0; i<engine->settings->maxParticleCount / particleSystems.size(); i++){
                for(unsigned int j=0; j<particleSystems.size(); j++){
                    particleSystems[j]->addParticle(std::make_unique<Speed_Gradient_Particle>(particleSystems[j]->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                        -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                        Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                    engine->settings->currentParticleCount++;
                }
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
            std::vector<std::thread> threads;
            for(unsigned int i=0; i<particleSystems.size(); i++){
                particleSystems[i]->setPosition(sf::Mouse::getPosition(engine->window));
                threads.push_back(std::thread([this, i, delta](){this->particleSystems[i]->update(delta);}));
            }
            for(unsigned int i=0; i<threads.size(); i++){
                threads[i].join();
            }
        }

        void draw(float delta){
            engine->window.clear();

            //std::vector<std::thread> threads;
            for(unsigned int i=0; i<particleSystems.size(); i++){
                //threads.push_back(std::thread([this, i, delta](){this->particleSystems[i]->draw(delta);}));
                particleSystems[i]->draw(delta);
            }
            // for(unsigned int i=0; i<threads.size(); i++){
            //     threads[i].join();
            // }

            engine->window.display();
        }
    };

} // namespace VeX

#endif // __MULTITHREADED_PARTICLE_DEMO_HPP__
