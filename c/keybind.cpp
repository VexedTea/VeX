#include "../h/keybind.hpp"

namespace VeX{
    
    Keybind::Keybind(const sf::Keyboard::Key & key, KeybindCondition conditionType, std::function<void()> action):
        key(key),
        action(action),
        keyPressed(sf::Keyboard::isKeyPressed(key)),
        prev(keyPressed)
    {
        switch(conditionType){
        case KeybindCondition::KeyPressed:
            condition = [&]()bool{return getKeyPressed();};
            break;
        case KeybindCondition::OnKeyDown:
            condition = [&]()bool{return onKeyDown();};
            break;
        case KeybindCondition::OnKeyUp:
            condition = [&]()bool{return onKeyUp();};
            break;
        }
    }

    void Keybind::update(){
        prev = keyPressed;
        keyPressed = sf::Keyboard::isKeyPressed(key);
        if(condition()){
            action();
        }
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
