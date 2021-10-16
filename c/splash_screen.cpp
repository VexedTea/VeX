#include "../h/splash_screen.hpp"

namespace VeX{

    Splash_Screen::Splash_Screen(const sf::Time & time, State_Ptr followUpState):
        time(time),
        followUpState(std::move(followUpState)),
        clock(),
        splash()
    {}
    
    void Splash_Screen::init(){
        splash.setTexture(engine->loadTexture("VexedTea", "assets/textures/VexedTea.png"));
        splash.setPosition(sf::Vector2f(engine->settings->screenWidth/2 - engine->getTexture("VexedTea").getSize().x/2, engine->settings->screenHeight/2 - engine->getTexture("VexedTea").getSize().y/2));
        unsigned int scale = engine->settings->screenHeight/engine->getTexture("VexedTea").getSize().y;
        splash.setScale(sf::Vector2f(scale,scale));
    }
    
    void Splash_Screen::handleInput(){
        //Handle ur input
        
        sf::Event event;
        while (engine->window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            engine->window.close();
        }
    }
    
    void Splash_Screen::update(float ){
        if(clock.getElapsedTime() > time){
            engine->addState(std::move(followUpState), true);
        }
    }
    
    void Splash_Screen::draw(float ){
        engine->window.clear();
        
        engine->window.draw(splash);
        
        engine->window.display();
    }

} // namespace VeX
