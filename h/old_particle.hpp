#ifndef __OLD_PARTICLE_HPP__
#define __OLD_PARTICLE_HPP__

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string>
#include <cmath>
#include "engine.hpp"
#include "definitions.hpp"
#include "color_gradient.hpp"

namespace VeX{

    class Old_Particle{
    private:
        Engine_Ptr engine;
        sf::Color color;
        Color_Gradient colors;
        bool usingGradient;
        std::string textureName;
        float mass;
        sf::Vector2f motionDampening;

        sf::Vector2f position;
        sf::Sprite sprite;
        sf::Vector2f velocity;
    public:
        bool deleteMe;

        Old_Particle(Engine_Ptr engine, const sf::Vector2f & _position, const sf::Color & color, const Color_Gradient & colors={{sf::Color::White}}, const bool & usingGradient=false,
            const std::string & textureName="defaultOld_Particle", const sf::IntRect & textureSection={0,0,0,0}, const sf::Vector2f & scale={1,1},
            const float & mass=1.f,
            const sf::Vector2f & randomStartVelocityAmp={100.f,100.f},
            const sf::Vector2f & randomStartPositionOffset={100.f,100.f},
            const sf::Vector2f & motionDampening=Definition::defaultParticleMotionDampening):
            engine(engine),
            color(color),
            colors(colors),
            usingGradient(usingGradient),
            textureName(textureName),
            mass(mass),
            motionDampening(motionDampening),
            deleteMe(false)
        {
            position = {
                _position.x + -randomStartPositionOffset.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(randomStartPositionOffset.x*2))),
                _position.y + -randomStartPositionOffset.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(randomStartPositionOffset.y*2)))
            };

            velocity = {-randomStartVelocityAmp.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(randomStartVelocityAmp.x*2))),
                        -randomStartVelocityAmp.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(randomStartVelocityAmp.y*2)))};

            sprite.setTexture(engine->loadTexture(textureName));
            sprite.setColor(color);
            sprite.setPosition(position);
            sprite.setScale(scale);
            if(textureSection!=sf::IntRect{0,0,0,0}){
                //std::cout<<textureSection.width<<"\n";
                sprite.setTextureRect(textureSection);
            }
        }

        Old_Particle(Engine_Ptr engine, const sf::Vector2f & _position, const sf::Color & color, const Color_Gradient & colors={{sf::Color::White}}, const bool & usingGradient=false,
            const std::string & textureName="defaultOld_Particle", const sf::Vector2f & scale={1,1}, const float & mass=1.f,
            const sf::Vector2f & randomStartVelocityAmp={100.f,100.f},
            const sf::Vector2f & randomStartPositionOffset={100.f,100.f},
            const sf::Vector2f & motionDampening=Definition::defaultParticleMotionDampening):
                Old_Particle(engine, _position, color, colors, usingGradient, textureName, {0,0,0,0}, scale, mass, randomStartVelocityAmp, randomStartPositionOffset, motionDampening)
            {}

        Old_Particle(Engine_Ptr engine, const sf::Vector2f & _position, const Color_Gradient & colors,
            const std::string & textureName="defaultOld_Particle", const sf::Vector2f & scale={1,1}, const float & mass=1.f,
            const sf::Vector2f & randomStartVelocityAmp={100.f,100.f},
            const sf::Vector2f & randomStartPositionOffset={100.f,100.f},
            const sf::Vector2f & motionDampening=Definition::defaultParticleMotionDampening):
                Old_Particle(engine, _position, sf::Color::White, colors, true, textureName, {0,0,0,0}, scale, mass, randomStartVelocityAmp, randomStartPositionOffset, motionDampening)
            {}

        Old_Particle(Engine_Ptr engine, const sf::Vector2f & _position, const std::string & textureName="defaultOld_Particle", const sf::IntRect & textureSection={0,0,0,0}, 
            const sf::Vector2f & scale={1,1}, const float & mass=1.f,
            const sf::Vector2f & randomStartVelocityAmp={100.f,100.f},
            const sf::Vector2f & randomStartPositionOffset={100.f,100.f},
            const sf::Vector2f & motionDampening=Definition::defaultParticleMotionDampening):
                Old_Particle(engine, _position, sf::Color::White, {{sf::Color::White}}, false, textureName, textureSection, scale, mass, 
                        randomStartVelocityAmp, randomStartPositionOffset, motionDampening)
            {}

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
            if(usingGradient){
                sprite.setColor(colors.getColorAt(sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) / 3500));
                //std::cout << "speed: " << sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) << "\n";
            }
            engine->window.draw(sprite);
        }

        void gravTo(const sf::Vector2f & targetPos, const float & delta){
            if(targetPos == position){return;}
            float magnitude = sqrt(pow(targetPos.x - position.x, 2) + pow(targetPos.y - position.y, 2));
            sf::Vector2f direction = (targetPos - position)/magnitude;
            float v = -0.4*magnitude + (Definition::gravitationalConstant * delta * pow(magnitude, 1.2)) + 3;
            velocity += direction * v;

            //std::cout << "position: " << position << "\ttargetPos: " << targetPos << "\tmagnitude: " << magnitude << "\tdirection: " << direction << "    \tv: " << v << "\tvelocity: " << velocity << "\n";
        }

        void applyForce(const sf::Vector2f & force){
            velocity += force / mass;
        }

        void move(const sf::Vector2f & movement){
            position += movement;
            sprite.setPosition(position);
        }
    };

}

#endif // __OLD_PARTICLE_HPP__
