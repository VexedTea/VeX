#include "../h/pause_menu.hpp"

namespace VeX{

    Pause_Menu::Pause_Menu(){}

    void Pause_Menu::init(){
        engine->addGlobalKeybind(
            "ToggleMenu", 
            sf::Keyboard::Key::Escape, 
            KeybindCondition::OnKeyUp, 
            [&](){
                engine->pauseMenuOpen = !engine->pauseMenuOpen;std::cout<<"pog";
            }
        );
        background.setTexture(engine->loadTexture("pause_menu_background", "assets/textures/ui/pause_menu_background.png"));
        background = snapTo(background, {0.5, 0.5}, {0.8, 0.8});
    }

    void Pause_Menu::handleInput(){
        //Handle ur input
        
        sf::Event event;
        while (engine->window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            engine->window.close();
        }
    }

    void Pause_Menu::update(float ){
        
    }

    void Pause_Menu::draw(float ){
        engine->window.draw(background);
    }

} // namespace VeX
