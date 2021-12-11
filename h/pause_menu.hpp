#ifndef __PAUSE_MENU_HPP__
#define __PAUSE_MENU_HPP__

#include "engine.hpp"
#include "state.hpp"
#include "ui/button.hpp"
#include "transform_util.hpp"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <functional>
#include <math.h>

#include <iostream>

namespace VeX{
    using State_Ptr = std::unique_ptr<State>;

    class Pause_Menu : public State{
    private:
        sf::Sprite background;
        std::vector<UI::Button> buttons;

        void arrangeButtons();
    public:
        Pause_Menu();
        
        void init();
        
        void handleInput();
        
        void update(float delta);
        
        void draw(float delta);

        void addStateSelection(const std::function<State_Ptr()> & makeState, const UI::Button_Data & optionData);
    };

} // namespace VeX

#endif // __PAUSE_MENU_HPP__
