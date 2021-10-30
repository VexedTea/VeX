#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <memory>
#include <stack>
#include <map>
#include "state_manager.hpp"
#include "asset_manager.hpp"
#include "settings.hpp"
#include "utilities.hpp"

namespace VeX{

    class Engine : public State_Manager, public Asset_Manager{
    private:
        const float delta;
        float framerate;
        Ringbuff<sf::Time> frametimes;
        sf::Font debugFont;
        sf::Text frameTimeText;
        sf::Text currentParticleCountText;

        sf::Clock clock;
    public:
        Engine(sf::RenderWindow & window);

        //float highestFrameTime;//Will introduce proper runtime statistics and stuff sometime
        //float startTime;
        sf::RenderWindow & window;
        Settings_Ptr settings;

        void runOnce(float & newTime, float & frameTime, float & interpolation, float & currentTime, float & accumulator);

        void run();

        void runPocketState(State_Ptr state);

        float getFramerate();

        void displayFramerate();

        void displayCurrentParticleCount();
    };

    using Engine_Ptr = std::shared_ptr<Engine>;
    extern sf::RenderWindow window;
    extern VeX::Engine_Ptr engine;
}

#endif // __ENGINE_HPP__
