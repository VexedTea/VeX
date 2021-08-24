#ifndef __PARTICLE_DEMO_HPP__
#define __PARTICLE_DEMO_HPP__

#include <vector>
#include <memory>

#include "speed_gradient_particle.hpp"
#include "particle_system.hpp"
#include "engine.hpp"
#include "utilities.hpp"

namespace VeX{

    class Particle_Demo : public State{
    private:
        bool circlePath;
        float circleAngle;
        std::unique_ptr<Particle_System> particleSystem;
        
    public:
        Particle_Demo(bool circlePath=false):
            circlePath(circlePath),
            circleAngle(0.f),
            particleSystem(std::make_unique<Particle_System>())            
        {}

        void init(){
            engine->addKeybind("resetState", sf::Keyboard::Key::Backspace);
            engine->addKeybind("circlePathToggle", sf::Keyboard::Key::O);
            particleSystem->setPosition(sf::Mouse::getPosition());
            // for(unsigned int i=0; i<engine->settings->maxParticleCount; i++){
            //     particleSystem->addParticle(std::make_unique<Speed_Gradient_Particle>(particleSystem->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
            //                                                             -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
            //                                                             Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
            //     engine->settings->currentParticleCount++;
            // }
        }

        void handleInput(){
            if(engine->getKeybind("resetState")->onKeyDown()){
                engine->settings->currentParticleCount = 0;
                engine->addState(std::make_unique<VeX::Particle_Demo>(circlePath), true);
            }

            if(engine->getKeybind("circlePathToggle")->onKeyDown()){
                circlePath = !circlePath;
            }

            sf::Event event;
            while (engine->window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    engine->window.close();
            }
        }

        void update(float delta){
            if(!circlePath){
                particleSystem->setPosition(sf::Mouse::getPosition(engine->window));
            }else{
                particleSystem->setPosition(getPositionOnCircle(engine->settings->getScreenCenter(), 500.f, circleAngle));
                circleAngle += 0.2 * delta;
                if(circleAngle >= 360.f){
                    circleAngle -= 360.f;
                }
            }

            if(engine->getFramerate() > 75.f){
                for(unsigned int i=0; i<25; i++){
                    particleSystem->addParticle(std::make_unique<Speed_Gradient_Particle>(particleSystem->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                        -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                        Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                    engine->settings->currentParticleCount++;
                }
            }else if(engine->getFramerate() < 62.f){
                particleSystem->removeOldestParticle();
                engine->settings->currentParticleCount--;
            }

            particleSystem->update(delta);
        }

        void draw(float delta){
            engine->window.clear();

            particleSystem->draw(delta);

            particleSystem->drawCenterPoint();
            engine->displayFramerate();
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __PARTICLE_DEMO_HPP__
