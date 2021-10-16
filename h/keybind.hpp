#ifndef __KEYBIND_HPP__
#define __KEYBIND_HPP__

#include "SFML/Graphics.hpp"

namespace VeX{
    
    class Keybind{
    private:
        sf::Keyboard::Key key;
        bool keyPressed;
        bool prev;
    public:
        Keybind(const sf::Keyboard::Key & key);

        void update();

        bool getKeyPressed();

        bool onKeyDown();

        bool onKeyUp();
    };

} // namespace VeX


#endif // __KEYBIND_HPP__
