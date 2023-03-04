#ifndef __VERLET_DEMO_HPP__
#define __VERLET_DEMO_HPP__

#include "verlet_solver.hpp"
#include "../definitions.hpp"
#include "../engine.hpp"
#include "../utilities.hpp"

#include <iostream>

namespace VeX{

    class Verlet_Demo : public State{
    private:
        Verlet_Solver solver;
        float objectSpawnDelay;
        float objectSpawnSpeed;
        sf::Vector2f objectSpawnPosition;
        float objectMinRadius;
        float objectMaxRadius;
        int maxObjectCount;
        float maxAngle;
        sf::Clock clock;

    public:
        Verlet_Demo()//:
        {
            std::cout << "Verlet_Demo contructor";
        }
        
        void init();
        
        void handleInput(){
            //Handle ur input
            
            sf::Event event;
            while (engine->window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                engine->window.close();
            }
        }
        
        void update(float /*delta*/);
        
        void draw(float /*delta*/);
    };

} // namespace VeX

#endif // __VERLET_DEMO_HPP__
