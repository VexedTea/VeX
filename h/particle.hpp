#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string>
#include <cmath>
#include "engine.hpp"
#include "definitions.hpp"

namespace VeX{

    class Particle{
    private:
        Engine & engine;
        std::string textureName;
        sf::Vector2f motionDampening;

        sf::Vector2f position;
        sf::Sprite sprite;
        sf::Vector2f velocity;
    public:
        bool deleteMe;

        Particle(Engine & engine, const sf::Vector2f & _position, 
            const std::string & textureName="defaultParticle", const sf::Vector2f & scale={1,1},
            const sf::Vector2f & randomStartVelocityAmp={100.f,100.f},
            const sf::Vector2f & randomStartPositionOffset={100.f,100.f},
            const sf::Vector2f & motionDampening=Definition::defaultParticleMotionDampening):
            engine(engine),
            textureName(textureName),
            motionDampening(motionDampening),
            deleteMe(false)
        {
            position = {
                _position.x + -randomStartPositionOffset.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(randomStartPositionOffset.x*2))),
                _position.y + -randomStartPositionOffset.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(randomStartPositionOffset.y*2)))
            };

            velocity = {-randomStartVelocityAmp.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(randomStartVelocityAmp.x*2))),
                        -randomStartVelocityAmp.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(randomStartVelocityAmp.y*2)))};

            sprite.setTexture(engine.loadTexture(textureName));
            sprite.setPosition(position);
            sprite.setScale(scale);
        }

        void update(const float & delta){
            // float maxVelocity = 100;
            // if(velocity.x > maxVelocity){velocity.x=maxVelocity;}
            // if(velocity.y > maxVelocity){velocity.y=maxVelocity;}
            // if(velocity.x < -maxVelocity){velocity.x=-maxVelocity;}
            // if(velocity.x < -maxVelocity){velocity.y=-maxVelocity;}
            if(position.x > (1+Definition::offScreenLimitMult) * Definition::screenWidth || position.x < -Definition::offScreenLimitMult * Definition::screenWidth || 
                position.y > (1+Definition::offScreenLimitMult) * Definition::screenHeight || position.y < -Definition::offScreenLimitMult * Definition::screenHeight){
                deleteMe = true;
                //std::cout << position.x << " " << position.y << "\n";
            }
            velocity = velocity / ((motionDampening * delta)+1);
            position += velocity * delta;
            sprite.setPosition(position);
        }

        void draw(const float &){
            engine.window.draw(sprite);
        }

        void gravTo(const sf::Vector2f & targetPos, const float & delta){
            if(targetPos == position){return;}
            float magnitude = sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
            sf::Vector2f direction = (targetPos - position)/magnitude;
            float v = -0.4*magnitude + (Definition::gravitationalConstant * delta * pow(magnitude, 1.2)) + 3;
            velocity += direction * v;

            //std::cout << "position: " << position << "\ttargetPos: " << targetPos << "\tmagnitude: " << magnitude << "\tdirection: " << direction << "    \tv: " << v << "\tvelocity: " << velocity << "\n";
        }
    };

}

#endif // __PARTICLE_HPP__
