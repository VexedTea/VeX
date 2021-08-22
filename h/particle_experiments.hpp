#ifndef __PARTICLE_EXPERIMENTS_HPP__
#define __PARTICLE_EXPERIMENTS_HPP__

#include "particle_system.hpp"
#include <string>

namespace VeX{

    class Particle_Experiments : public State{
    private:
        Particle_System particleSystem;

        //Debug stuffs
        sf::Clock niceClock;
        sf::Time prevDrawCallTime;
        sf::Font debugFont;
        sf::Text frameTimeText;

        void addDefaultParticles(){
            engine->loadTexture("Particle", "assets/textures/particle.png");
            for(unsigned int i=0; i<engine->settings->maxParticleCount; i++){
                particleSystem.addParticle(std::make_unique<Particle>(particleSystem.getPosition() + sf::Vector2f{-100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2))),
                                                                    -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(100*2)))},
                                                                    engine->getTexture("Particle"),
                                                                    Definition::defaultParticleMotionDampening));
                engine->settings->currentParticleCount++;
            }
        }

    public:
        Particle_Experiments():
            particleSystem(),
            niceClock(),
            prevDrawCallTime(niceClock.getElapsedTime())
        {}/* e5upSHu.jpg */
        
        void init(){

            particleSystem.setPosition(sf::Vector2f(engine->settings->screenWidth/2, engine->settings->screenHeight/2));
            
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
            particleSystem.setPosition(sf::Mouse::getPosition(engine->window));
            particleSystem.update(delta);
        }
        
        void draw(float delta){
            sf::Time currentTime = niceClock.getElapsedTime();
            frameTimeText.setString(std::to_string( 1000/(currentTime.asMilliseconds() - prevDrawCallTime.asMilliseconds())));
            prevDrawCallTime = currentTime;

            engine->window.clear();
            
            engine->window.draw(frameTimeText);
            particleSystem.draw(delta);
            
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __PARTICLE_EXPERIMENTS_HPP__
