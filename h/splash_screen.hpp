#ifndef __SPLASH_SCREEN_HPP__
#define __SPLASH_SCREEN_HPP__

#include "engine.hpp"

namespace VeX{

    class Splash_Screen : public State{
    private:
        sf::Time time;
        State_Ptr followUpState;

        sf::Clock clock;
        sf::Sprite splash;
    public:
        Splash_Screen(const sf::Time & time, State_Ptr followUpState);
        
        void init();
        
        void handleInput();
        
        void update(float );
        
        void draw(float );
    };

} // namespace VeX

#endif // __SPLASH_SCREEN_HPP__
