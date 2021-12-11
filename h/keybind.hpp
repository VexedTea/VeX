#ifndef __KEYBIND_HPP__
#define __KEYBIND_HPP__

#include "SFML/Graphics.hpp"
#include <functional>

namespace VeX{
    enum class KeybindCondition{
        KeyPressed,
        OnKeyDown,
        OnKeyUp
    };
    
    class Keybind{
    private:
        sf::Keyboard::Key key;
        std::function<void()> action;
        std::function<bool()> condition;
        bool keyPressed;
        bool prev;
    public:
        Keybind(const sf::Keyboard::Key & key, KeybindCondition conditionType, std::function<void()> action);

        void update();

        bool getKeyPressed();

        bool onKeyDown();

        bool onKeyUp();
    };

} // namespace VeX


#endif // __KEYBIND_HPP__
