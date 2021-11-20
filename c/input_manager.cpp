#include "../h/input_manager.hpp"

namespace VeX{

    void Input_Manager::updateInputs(){
        for (auto const& keybind : globalKeybinds){
            keybind.second->update();
        }
        for (auto const& keybind : keybinds.top()){
            keybind.second->update();
        }
        leftClickPrev = leftClickPressed;
        leftClickPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        rightClickPrev = rightClickPressed;
        rightClickPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
    }

    void Input_Manager::addKeybind(const std::string & name, 
                    const sf::Keyboard::Key & key, 
                    KeybindCondition condition, 
                    std::function<void()> action){
        keybinds.top().emplace(name, std::make_unique<Keybind>(key, condition, action));
    }

    void Input_Manager::addGlobalKeybind(const std::string & name, 
                    const sf::Keyboard::Key & key, 
                    KeybindCondition condition, 
                    std::function<void()> action){
        globalKeybinds.emplace(name, std::make_unique<Keybind>(key, condition, action));
    }

    std::unique_ptr<Keybind> & Input_Manager::getKeybind(const std::string & name){
        const auto& item = keybinds.top().find(name);

        if (item == keybinds.top().end()) {
            std::cerr << "[VeX WARNING] Unable to get asset of type 'Keybind' with name '" << name << "'.\n";
        }
        return item->second; //Second is the value, first should be the key
    }

    bool Input_Manager::onLeftClick(){
        return (!leftClickPrev && leftClickPressed);
    }

    bool Input_Manager::onLeftClickRelease(){
        return (leftClickPrev && !leftClickPressed);
    }

    bool Input_Manager::onRightClick(){
        return (!rightClickPrev && rightClickPressed);
    }

    bool Input_Manager::onRightClickRelease(){
        return (rightClickPrev && !rightClickPressed);
    }
    
}
