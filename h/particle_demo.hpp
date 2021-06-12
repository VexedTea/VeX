#ifndef __PARTICLE_DEMO_HPP__
#define __PARTICLE_DEMO_HPP__

#include "SFML/Graphics.hpp"
#include <string>

#include "particle_system_factory.hpp"
#include "definitions.hpp"

#include "color_gradient.hpp"

namespace VeX {

    class Particle_Demo : public State{
    private:
        Engine & engine;
        Particle_System_Ptr particleSystem;

        bool followingMouse;
        bool paused;
    public:
        Particle_Demo(Engine & engine):
            engine(engine),
            //particleSystem(Particle_System_Factory::makePixelSizedParticleSystem(engine, Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 32'000)),
            //particleSystem(Particle_System_Factory::makePixelSizedParticleSystem(engine, {255,255,255}, 32'000)),
            particleSystem(std::make_unique<Particle_System>(engine)),
            followingMouse(false),
            paused(true)
        {}

        void init(){
            
            particleSystem = Particle_System_Factory::makeParticleSystemFromImage(engine, Definition::textures["demoImage"], 32'000, sf::Vector2f{Definition::screenWidth/2, Definition::screenHeight/2});

            particleSystem->setPosition(sf::Vector2f{Definition::screenWidth/2, Definition::screenHeight/2});
            // engine.makeRectangleTexture("testGradient", {Definition::screenWidth/2, Definition::screenHeight/2}, Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}));

            engine.addKeybind("resetState", sf::Keyboard::Key::Backspace);
            engine.addKeybind("particlePushUp", sf::Keyboard::Key::Up);
            engine.addKeybind("particlePushLeft", sf::Keyboard::Key::Left);
            engine.addKeybind("particlePushDown", sf::Keyboard::Key::Down);
            engine.addKeybind("particlePushRight", sf::Keyboard::Key::Right);
            engine.addKeybind("toggleMouseFollow", sf::Keyboard::Key::Enter);
            engine.addKeybind("pause", sf::Keyboard::Key::Space);
        }

        void handleInput(){
            //Handle ur input
            if(engine.getKeybind("resetState")->onKeyDown()){
                engine.addState(std::make_unique<VeX::Particle_Demo>(engine), true);
            }
            if(engine.getKeybind("particlePushLeft")->onKeyDown()){
                particleSystem->applyForceToAll(sf::Vector2f{-1.f,0.f}*1000);
            }else if(engine.getKeybind("particlePushRight")->onKeyDown()){
                particleSystem->applyForceToAll(sf::Vector2f{1.f,0.f}*1000);
            }
            if(engine.getKeybind("particlePushUp")->onKeyDown()){
                particleSystem->applyForceToAll(sf::Vector2f{0.f,-1.f}*1000);
            }else if(engine.getKeybind("particlePushDown")->onKeyDown()){
                particleSystem->applyForceToAll(sf::Vector2f{0.f,1.f}*1000);
            }
            if(engine.getKeybind("toggleMouseFollow")->onKeyDown()){
                followingMouse = !followingMouse;
            }
            if(engine.getKeybind("pause")->onKeyDown()){
                paused = !paused;
            }

            sf::Event event;
            while (engine.window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    engine.window.close();
            }
        }

        void update(float delta){
            if(!paused){
                if(followingMouse){particleSystem->setPosition(sf::Mouse::getPosition(engine.window));}
                particleSystem->update(delta);
            }
        }

        void draw(float delta){
            engine.window.clear();

            // sf::Sprite testGradient(engine.getTexture("testGradient"));
            // testGradient.setPosition({Definition::screenWidth/4, Definition::screenHeight/4});
            // engine.window.draw(testGradient);

            particleSystem->draw(delta);

            engine.window.display();
        }
    };

}

#endif // __PARTICLE_DEMO_HPP__
