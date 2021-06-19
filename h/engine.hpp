#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <memory>
#include <stack>
#include <map>
#include "state_machine.hpp"
#include "asset_manager.hpp"
#include "input_manager.hpp"
#include "settings.hpp"

namespace VeX{

    class Engine : public State_Machine, public Asset_Manager, public Input_Manager{
    private:
        const float delta;
        sf::Clock clock;

    public:
        Engine(sf::RenderWindow & window):
            State_Machine(),
            Asset_Manager(),
            delta(1.f/60.f),
            window(window),
            settings(std::make_unique<Settings>())
        {}

        sf::RenderWindow & window;
        Settings_Ptr settings;

        void run(){ //Have a look at the frametiming stuff again
            float newTime, frameTime, interpolation;
            float currentTime = clock.getElapsedTime().asSeconds();
            float accumulator = 0.0f;
            while (window.isOpen()){
                processStateChanges();

                newTime = clock.getElapsedTime().asSeconds();
                frameTime = newTime - currentTime;
                if (frameTime > 0.25f) {
                frameTime = 0.25f;
                }
                currentTime = newTime;
                accumulator += frameTime;
                std::cout << "Frametime: " << frameTime << "\n";
                while (accumulator >= delta) {
                    updateKeybinds();
                    getActiveState()->handleInput();
                    getActiveState()->update(delta);
                    accumulator -= delta;
                }
                interpolation = accumulator/delta;
                getActiveState()->draw(interpolation);
            }
        }
    };

    using Engine_Ptr = std::shared_ptr<Engine>;
    sf::RenderWindow window;
    
    VeX::Engine_Ptr engine = std::make_shared<VeX::Engine>(window); 
}

#endif // __ENGINE_HPP__

//We want to ask everything to the engine, hey engine, load me an image, hey engine, give me sum physics
//But that means we'll have 'engine' in our code like half a million times, which we dont want.