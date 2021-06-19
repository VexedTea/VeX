#ifndef __STATE_TEMPLATE_HPP__
#define __STATE_TEMPLATE_HPP__

namespace VeX{

    class StateTemplate : public State{
    private:
        
    public:
        StateTemplate():
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

}

#endif // __STATE_TEMPLATE_HPP__
