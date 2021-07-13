#ifndef __GRAV_HPP__
#define __GRAV_HPP__

#include <vector>

namespace VeX{
    enum class Mode{default, placing};

    class Grav : public State{
    private:

        Mode mode;
        std::vector<Object> bodies;
    public:
        Grav():
            mode(Mode::default)
            bodies()
        {}
        
        void init(){
            //Init ur shit
        }
        
        void handleInput(){
            //Handle ur input
            
            sf::Event event;
            while (engine->window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                engine->window.close();
            }
        }
        
        void update(float delta){
            //Update ur shit
        }
        
        void draw(float delta){
            engine->window.clear();
            
            //Draw ur shit
            
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __GRAV_HPP__
