#ifndef __INPUT_MANAGER_HPP__
#define __INPUT_MANAGER_HPP__

#include <memory>
#include <string>

#include "keybind.hpp"

namespace VeX{
    class Input_Manager{
    private:
        std::map<std::string, std::unique_ptr<Keybind>> keybinds;
    public:
        void updateKeybinds(){
            for (auto const& keybind : keybinds){
                keybind.second->update();
            }
        }

        void addKeybind(const std::string & name, const sf::Keyboard::Key & key){
            keybinds.emplace(name, std::make_unique<Keybind>(key));
        }

        std::unique_ptr<Keybind> & getKeybind(const std::string & name){
            const auto& item = keybinds.find(name);

            if (item == keybinds.end()) {
                std::cerr << "[VeX WARNING] Unable to get asset of type 'Keybind' with name '" << name << "'.\n";
            }
            return item->second; //Second is the value, first should be the key
        }
    };
}
#endif // __INPUT_MANAGER_HPP__
