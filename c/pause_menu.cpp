#include "../h/pause_menu.hpp"

namespace VeX{

    Pause_Menu::Pause_Menu()
    {}

    void Pause_Menu::init(){

    }

    void Pause_Menu::handleInput(){
        //Handle ur input
        
        sf::Event event;
        while (engine->window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            engine->window.close();
        }
    }

    void Pause_Menu::update(float delta){
        std::cout << delta;
    }

    void Pause_Menu::draw(float delta){
        std::cout << delta;
    }

} // namespace VeX
