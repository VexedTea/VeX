#ifndef __KEYBIND_HPP__
#define __KEYBIND_HPP__

namespace VeX{
    
    class Keybind{
    private:
        sf::Keyboard::Key key;
        bool keyPressed;
        bool prev;
    public:
        Keybind(const sf::Keyboard::Key & key):
            key(key),
            keyPressed(sf::Keyboard::isKeyPressed(key)),
            prev(keyPressed)
        {}

        void update(){
            prev = keyPressed;
            keyPressed = sf::Keyboard::isKeyPressed(key);
        }

        bool getKeyPressed(){
            return keyPressed;
        }

        bool onKeyDown(){ //Returns true when the key goes down. (when keyPressed was false but the key is now pressed)
            return (!prev && keyPressed);
        }

        bool onKeyUp(){ //Returns true when the key goes up. (when keyPressed was true but the key is now not pressed)
            return (prev && !keyPressed);
        }
    };

} // namespace VeX


#endif // __KEYBIND_HPP__
