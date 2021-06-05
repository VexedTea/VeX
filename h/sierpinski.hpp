#ifndef __SIERPINSKI_HPP__
#define __SIERPINSKI_HPP__

#include "state.hpp"
#include "engine.hpp"
#include "SFML/Graphics.hpp"
#include "definitions.hpp"

namespace VeX{

    //First ever state, was independant program before. Therefore doesnt utilise a lot of engine functionality.
    class Sierpinski : public State{
    private:
        Engine & engine;

        sf::Image triangleThingy;
        sf::Texture triangleMaybe;
        sf::Sprite triangleIGuess;
        sf::Vector2u posIterator;
    public:
        Sierpinski(Engine & engine):
            engine(engine)
        {}

        void init(){
            triangleThingy.create(Definition::screenWidth, Definition::screenHeight, sf::Color::Black);
            triangleMaybe.loadFromImage(triangleThingy);
            triangleThingy.setPixel(posIterator.x, posIterator.y, sf::Color::White);
            triangleIGuess = sf::Sprite(triangleMaybe);
            posIterator = sf::Vector2u(0,0);
        }

        void handleInput(){
            
        }

        void update(float){
            sf::Event event;
            while (engine.window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    engine.window.close();
            }
        }

        void draw(float){
            engine.window.clear();
            triangleMaybe.update(triangleThingy);
            engine.window.draw(triangleIGuess);
            for(unsigned int i=0; i<triangleThingy.getSize().x; i++){
                unsigned int triangleValue=0;
                if(posIterator.x > 0){
                    if(triangleThingy.getPixel(posIterator.x-1, posIterator.y) == sf::Color::White){
                        triangleValue++;
                    }
                }
                if(posIterator.y > 0){
                    if(triangleThingy.getPixel(posIterator.x, posIterator.y-1) == sf::Color::White){
                        triangleValue++;
                    }
                }
                if(triangleValue == 1){
                    triangleThingy.setPixel(posIterator.x, posIterator.y, sf::Color::White);
                }
                if(posIterator.x < triangleThingy.getSize().x-1){
                    posIterator.x++;
                }else if(posIterator.y < triangleThingy.getSize().y-1){
                    posIterator.y++;
                    posIterator.x=0;
                }
            }
            //sf::sleep(sf::milliseconds(10));
            
            engine.window.display();
        }
    };

}

#endif // __SIERPINSKI_HPP__
