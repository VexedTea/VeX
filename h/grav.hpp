#ifndef __GRAV_HPP__
#define __GRAV_HPP__

#include <vector>
#include "gravitational_system.hpp"
#include "circle_object.hpp"

namespace VeX{
    enum class Mode{none, placing};

    // struct placingModeData{
        

    // };

    class Grav : public State{
    private:
        Mode mode;
        Gravitational_System gravSystem;
        sf::Vector2f placingStartPoint;
    public:
        Grav():
            mode(Mode::none),
            gravSystem()
        {}
        
        void init(){

        }
        
        void handleInput(){
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
        
        void update(float delta){
            gravSystem.update(delta);
        }
        
        void draw(float delta){
            engine->window.clear(sf::Color(13, 0, 60));
            
            gravSystem.draw(delta);
            
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __GRAV_HPP__
