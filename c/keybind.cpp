#include "../h/keybind.hpp"

namespace VeX{
    
    Keybind::Keybind(const sf::Keyboard::Key & key):
        key(key),
        keyPressed(sf::Keyboard::isKeyPressed(key)),
        prev(keyPressed)
    {}

    void Keybind::update(){
        prev = keyPressed;
        keyPressed = sf::Keyboard::isKeyPressed(key);
    }

    bool Keybind::getKeyPressed(){
        return keyPressed;
    }

    bool Keybind::onKeyDown(){ //Returns true when the key goes down. (when keyPressed was false but the key is now pressed)
        return (!prev && keyPressed);
    }

    bool Keybind::onKeyUp(){ //Returns true when the key goes up. (when keyPressed was true but the key is now not pressed)
        return (prev && !keyPressed);
    }

} // namespace VeX
