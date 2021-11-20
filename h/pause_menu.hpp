#ifndef __PAUSE_MENU_HPP__
#define __PAUSE_MENU_HPP__

#include "SFML/Graphics.hpp"
#include <iostream>

#include "engine.hpp"
#include "state.hpp"
#include "transform_util.hpp"

namespace VeX{

    class Pause_Menu : public State{
    private:
        sf::Sprite background;
    public:
        Pause_Menu();
        
        void init();
        
        void handleInput();
        
        void update(float delta);
        
        void draw(float delta);
    };

} // namespace VeX

#endif // __PAUSE_MENU_HPP__
