#ifndef __PARTICLE_DEMO_HPP__
#define __PARTICLE_DEMO_HPP__

#include "SFML/Graphics.hpp"

#include "particle_system_factory.hpp"
#include "definitions.hpp"

#include "color_gradient.hpp"

namespace VeX {

    class Particle_Demo : public State{
    private:
        Engine & engine;
        Particle_System_Ptr particleSystem;

    public:
        Particle_Demo(Engine & engine):
            engine(engine),
            particleSystem(Particle_System_Factory::makePixelSizedParticleSystem(engine, Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}), 32'000))
            //particleSystem(Particle_System_Factory::makePixelSizedParticleSystem(engine, {255,255,255}, 32'000))
        {}

        void init(){
            particleSystem->setPosition({Definition::screenWidth/2, Definition::screenHeight/2});\
            //engine.makeRectangleTexture("testGradient", {Definition::screenWidth/2, Definition::screenHeight/2}, Color_Gradient({{102, 31, 196}, {21, 232, 255}, {255,255,255}}));
        }

        void handleInput(){
            //Handle ur input
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)){
                engine.addState(std::make_unique<VeX::Particle_Demo>(engine), true);
            }

            sf::Event event;
            while (engine.window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    engine.window.close();
            }
        }

        void update(float delta){
            particleSystem->update(delta);
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
