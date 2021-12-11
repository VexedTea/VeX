#ifndef __INPUT_MANAGER_HPP__
#define __INPUT_MANAGER_HPP__

#include <memory>
#include <stack>
#include <string>
#include <iostream>
#include <functional>
#include "SFML/Graphics.hpp"

#include "keybind.hpp"

namespace VeX{

    class Input_Manager{
    protected:
        std::stack<std::map<std::string, std::unique_ptr<Keybind>>> keybinds;
        std::map<std::string, std::unique_ptr<Keybind>> globalKeybinds;
    private:
        bool leftClickPressed = false;
        bool leftClickPrev = false;
        bool rightClickPressed = false;
        bool rightClickPrev = false;
        
    public:
        void updateInputs();

        void addKeybind(const std::string & name, 
                        const sf::Keyboard::Key & key, 
                        KeybindCondition condition, 
                        std::function<void()> action);

        void addGlobalKeybind(const std::string & name, 
                                            const sf::Keyboard::Key & key, 
                                            KeybindCondition condition, 
                                            std::function<void()> action);

        std::unique_ptr<Keybind> & getKeybind(const std::string & name);

        bool onLeftClick();

        bool onLeftClickRelease();

        bool onRightClick();

        bool onRightClickRelease();

        sf::Vector2f getMousePos(const sf::Window & window);
    };
}
#endif // __INPUT_MANAGER_HPP__
