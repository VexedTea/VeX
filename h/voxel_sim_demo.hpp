#ifndef __VOXEL_SIM_DEMO_HPP__
#define __VOXEL_SIM_DEMO_HPP__

#include "voxel_sim.hpp"

namespace VeX{

    class Voxel_Sim_Demo : public State{
    private:
        Voxel_Sim voxelSim;

        //Debug stuffs
        sf::Clock niceClock;
        sf::Time prevDrawCallTime;
        sf::Font debugFont;
        sf::Text frameTimeText;

    public:
        Voxel_Sim_Demo():
            voxelSim(4),
            niceClock(),
            prevDrawCallTime(niceClock.getElapsedTime())
        {}
        
        void init(){
            

            if(!debugFont.loadFromFile("assets/fonts/Arial_GEO.TTF")){
                std::cout << "Particle_Experiments: Failed to load debugFont" << std::endl;
            }
            frameTimeText.setFont(debugFont);
            frameTimeText.setString("First frame!");
            frameTimeText.setCharacterSize(24);
            frameTimeText.setFillColor(sf::Color::White);
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
            voxelSim.update(delta);
        }
        
        void draw(float ){
            sf::Time currentTime = niceClock.getElapsedTime();
            frameTimeText.setString(std::to_string( 1000/(currentTime.asMilliseconds() - prevDrawCallTime.asMilliseconds())));
            prevDrawCallTime = currentTime;

            engine->window.clear();
            
            engine->window.draw(frameTimeText);
            
            voxelSim.draw();
            
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __VOXEL_SIM_DEMO_HPP__
