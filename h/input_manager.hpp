#ifndef __INPUT_MANAGER_HPP__
#define __INPUT_MANAGER_HPP__

#include <memory>
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"

#include "keybind.hpp"

namespace VeX{
    class Input_Manager{
    private:
        std::map<std::string, std::unique_ptr<Keybind>> keybinds;
        bool leftClickPressed = false;
        bool leftClickPrev = false;
        bool rightClickPressed = false;
        bool rightClickPrev = false;
    public:
        void updateInputs();

        void addKeybind(const std::string & name, const sf::Keyboard::Key & key);

        std::unique_ptr<Keybind> & getKeybind(const std::string & name);

        bool onLeftClick();

        bool onLeftClickRelease();

        bool onRightClick();

        bool onRightClickRelease();
    };
}
#endif // __INPUT_MANAGER_HPP__
