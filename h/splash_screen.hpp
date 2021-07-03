#ifndef __SPLASH_SCREEN_HPP__
#define __SPLASH_SCREEN_HPP__

#include "engine.hpp"

namespace VeX{

    class Splash_Screen : public State{
    private:
        sf::Time time;
        State_Ptr followUpState;

        sf::Clock clock;
        sf::Sprite splash;
    public:
        Splash_Screen(const sf::Time & time, State_Ptr followUpState):
            time(time),
            followUpState(std::move(followUpState)),
            clock(),
            splash()
        {}
        
        void init(){
            splash.setTexture(engine->loadTexture("VexedTea", "assets/textures/VexedTea.png"));
            splash.setPosition(sf::Vector2f(engine->settings->screenWidth/2 - engine->getTexture("VexedTea").getSize().x/2, engine->settings->screenHeight/2 - engine->getTexture("VexedTea").getSize().y/2));
            unsigned int scale = engine->settings->screenHeight/engine->getTexture("VexedTea").getSize().y;
            splash.setScale(sf::Vector2f(scale,scale));
        }
        
        void handleInput(){
            //Handle ur input
            
            sf::Event event;
            while (engine->window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                engine->window.close();
            }
        }
        
        void update(float ){
            if(clock.getElapsedTime() > time){
                engine->addState(std::move(followUpState), true);
            }
        }
        
        void draw(float ){
            engine->window.clear();
            
            engine->window.draw(splash);
            
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __SPLASH_SCREEN_HPP__
