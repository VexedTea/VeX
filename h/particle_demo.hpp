#ifndef __PARTICLE_DEMO_HPP__
#define __PARTICLE_DEMO_HPP__

#include <vector>
#include <memory>

#include "vertex_particle.hpp"
#include "vertex_particle_system.hpp"
#include "engine.hpp"
#include "utilities.hpp"

namespace VeX{

    class Particle_Demo : public State{
    private:
        bool circlePath;
        bool circlePaused;
        bool showCenters;
        bool drawParticles;
        bool maxParticleCountReached;
        float circleAngle;
        unsigned int primitiveTypeIndex;
        std::vector<sf::PrimitiveType> primitiveTypes;
        std::unique_ptr<Vertex_Particle_System> particleSystem;
        std::unique_ptr<Vertex_Particle_System> particleSystem1;
        std::unique_ptr<Vertex_Particle_System> particleSystem2;
        std::unique_ptr<Vertex_Particle_System> particleSystem3;
        
    public:
        Particle_Demo(bool circlePath=true, bool circlePaused=false):
            circlePath(circlePath),
            circlePaused(circlePaused),
            showCenters(false),
            drawParticles(true),
            maxParticleCountReached(false),
            circleAngle(0.f),
            primitiveTypeIndex(0),
            primitiveTypes({sf::PrimitiveType::Points, sf::PrimitiveType::Lines, sf::PrimitiveType::LineStrip, sf::PrimitiveType::Triangles, sf::PrimitiveType::TriangleStrip, sf::PrimitiveType::TriangleFan, sf::PrimitiveType::Quads}),
            particleSystem(std::make_unique<Vertex_Particle_System>()),
            particleSystem1(std::make_unique<Vertex_Particle_System>()),
            particleSystem2(std::make_unique<Vertex_Particle_System>()),
            particleSystem3(std::make_unique<Vertex_Particle_System>())            
        {}

        void init(){
            engine->addKeybind("resetState", sf::Keyboard::Key::Backspace);
            engine->addKeybind("circlePathToggle", sf::Keyboard::Key::O);
            engine->addKeybind("circlePauseToggle", sf::Keyboard::Key::P);
            engine->addKeybind("showCenters", sf::Keyboard::Key::L);
            engine->addKeybind("drawParticles", sf::Keyboard::Key::K);
            engine->addKeybind("nextPrimitiveType", sf::Keyboard::Key::Add);
            engine->addKeybind("prevPrimitiveType", sf::Keyboard::Key::Subtract);
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

            if(engine->getKeybind("circlePauseToggle")->onKeyDown()){
                circlePaused = !circlePaused;
            }

            if(engine->getKeybind("showCenters")->onKeyDown()){
                showCenters = !showCenters;
            }

            if(engine->getKeybind("drawParticles")->onKeyDown()){
                drawParticles = !drawParticles;
            }

            if(engine->getKeybind("nextPrimitiveType")->onKeyDown()){
                if(primitiveTypeIndex >= primitiveTypes.size()-1){
                    primitiveTypeIndex = 0;
                }else{
                    primitiveTypeIndex++;
                }
                particleSystem->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                particleSystem1->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                particleSystem2->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                particleSystem3->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                std::cout << primitiveTypeIndex << std::endl;
            }

            if(engine->getKeybind("prevPrimitiveType")->onKeyDown()){
                if(primitiveTypeIndex < 1){
                    primitiveTypeIndex = primitiveTypes.size()-1;
                }else{
                    primitiveTypeIndex--;
                }
                particleSystem->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                particleSystem1->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                particleSystem2->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                particleSystem3->setPrimitiveType(primitiveTypes[primitiveTypeIndex]);
                std::cout << primitiveTypeIndex << std::endl;
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
            }else if(!circlePaused){
                particleSystem->setPosition(getPositionOnCircle(engine->settings->getScreenCenter(), 400.f, circleAngle));
                particleSystem1->setPosition(getPositionOnCircle(engine->settings->getScreenCenter(), 400.f, circleAngle+90.f));
                particleSystem2->setPosition(getPositionOnCircle(engine->settings->getScreenCenter(), 400.f, circleAngle+180.f));
                particleSystem3->setPosition(getPositionOnCircle(engine->settings->getScreenCenter(), 400.f, circleAngle+270.f));
                circleAngle += 1.65 * 360.f * delta;
                if(circleAngle >= 360.f){
                    circleAngle -= 360.f;
                }   //0.215 & 500.f highest known to inhibit effect and 0.191 smallest known
            }

            if(engine->getFramerate() > 75.f && !maxParticleCountReached){
                for(unsigned int i=0; i<20; i++){
                    particleSystem->addParticle(std::make_unique<Vertex_Particle>(particleSystem->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                        -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                        Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                    particleSystem1->addParticle(std::make_unique<Vertex_Particle>(particleSystem1->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                        -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                        Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                    particleSystem2->addParticle(std::make_unique<Vertex_Particle>(particleSystem2->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                        -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                        Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                    particleSystem3->addParticle(std::make_unique<Vertex_Particle>(particleSystem3->getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                                        -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))}, Definition::defaultParticleMotionDampening,
                                                                                        Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 3500.f));
                    engine->settings->currentParticleCount += 4;
                }
            }else if(engine->getFramerate() < 62.f){
                particleSystem->removeOldestParticle();
                particleSystem1->removeOldestParticle();
                particleSystem2->removeOldestParticle();
                particleSystem3->removeOldestParticle();
                engine->settings->currentParticleCount -= 4;
                maxParticleCountReached = true;
            }

            particleSystem->update(delta);
            particleSystem1->update(delta);
            particleSystem2->update(delta);
            particleSystem3->update(delta);
        }

        void draw(float delta){
            engine->window.clear();

            if(drawParticles){
                particleSystem->draw(delta);
                particleSystem1->draw(delta);
                particleSystem2->draw(delta);
                particleSystem3->draw(delta);
            }
            
            if(showCenters){
                particleSystem->drawCenterPoint();
                particleSystem1->drawCenterPoint();
                particleSystem2->drawCenterPoint();
                particleSystem3->drawCenterPoint();
            }

            engine->displayFramerate();
            engine->displayCurrentParticleCount();
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __PARTICLE_DEMO_HPP__
