#ifndef __PARTICLE_DEMO_HPP__
#define __PARTICLE_DEMO_HPP__

#include "SFML/Graphics.hpp"

#include "particle_system.hpp"
#include "definitions.hpp"

namespace VeX {

    class Particle_Demo : public State{
    private:
        Engine & engine;
        ParticleSystem particleSystem;

    public:
        Particle_Demo(Engine & engine):
            engine(engine),
            particleSystem(engine, 10000)
        {}

        void init(){
            particleSystem.setPosition({Definition::screenWidth/2, Definition::screenHeight/2});
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
            particleSystem.update(delta);
        }

        void draw(float delta){
            engine.window.clear();

            particleSystem.draw(delta);

            engine.window.display();
        }
    };

}

#endif // __PARTICLE_DEMO_HPP__
