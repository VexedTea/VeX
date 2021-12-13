#include "../../h/demo/grav.hpp"

namespace VeX{

    Grav::Grav():
        mode(Mode::none),
        gravSystem()
    {}
    
    void Grav::init(){
        engine->settings->backgroundColor = sf::Color(13, 0, 60);

        // gravSystem.addBody(std::make_unique<Circle_Object>(
        //     engine->settings->getScreenCenter(),
        //     50.f,
        //     sf::Color(50,50,50),
        //     // magnitude(placingStartPoint - static_cast<sf::Vector2f>(sf::Mouse::getPosition(engine->window))) * pow(10.f, 14.f),
        //     // sf::Vector2f{0.f,0.f}
        //     pow(10.f, 18.f),
        //     sf::Vector2f{0.f,0.f}
        // ));
    }
    
    void Grav::handleInput(){
        switch(mode){
            case Mode::none:
                if(engine->onLeftClick()){
                    placingStartPoint = static_cast<sf::Vector2f>(sf::Mouse::getPosition(engine->window));
                    mode = Mode::placing;
                }
                break;
            case Mode::placing:
                if(engine->onLeftClickRelease()){
                    gravSystem.addBody(std::make_unique<Circle_Object>(
                        placingStartPoint,
                        10.f,
                        sf::Color(100,100,100),
                        // magnitude(placingStartPoint - static_cast<sf::Vector2f>(sf::Mouse::getPosition(engine->window))) * pow(10.f, 14.f),
                        // sf::Vector2f{0.f,0.f}
                        pow(10.f, 15.f),
                        placingStartPoint - static_cast<sf::Vector2f>(sf::Mouse::getPosition(engine->window))
                    ));
                    mode = Mode::none;
                }
                break;
        }
        
        sf::Event event;
        while (engine->window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            engine->window.close();
        }
    }
    
    void Grav::update(float delta){
        gravSystem.update(delta);
    }
    
    void Grav::draw(float delta){
        gravSystem.draw(delta);
    }

    void Grav::stop(){
        engine->settings->backgroundColor = sf::Color::Black;
    }

} // namespace VeX
