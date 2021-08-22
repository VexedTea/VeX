#ifndef __GRAVITATIONAL_SYSTEM_HPP__
#define __GRAVITATIONAL_SYSTEM_HPP__

#include "utilities.hpp"
#include "circle_object.hpp"
#include "definitions.hpp"

namespace VeX{

    class Gravitational_System{
    private:
        std::vector<std::unique_ptr<Circle_Object>> bodies;
    public:
        Gravitational_System():
            bodies()
        {}

        void update(float delta){
            for(unsigned int i=0; i<bodies.size(); i++){
                for(unsigned int j=i+1; j<bodies.size(); j++){
                    if(bodies[i]->getPosition() != bodies[j]->getPosition()){
                        bodies[i]->addVelocity(normalize(bodies[j]->getPosition() - bodies[i]->getPosition()) * delta * Definition::G * (sf::Vector2f(bodies[j]->getMass(), bodies[j]->getMass())/pow(distance(bodies[i]->getPosition(), bodies[j]->getPosition()),2)));
                        bodies[j]->addVelocity(normalize(bodies[i]->getPosition() - bodies[j]->getPosition()) * delta * Definition::G * (sf::Vector2f(bodies[i]->getMass(), bodies[i]->getMass())/pow(distance(bodies[i]->getPosition(), bodies[j]->getPosition()),2)));
                        // if(i==0 && j==1){
                        //     std::cout << delta * Definition::G * (sf::Vector2f(bodies[i]->getMass(), bodies[i]->getMass())/pow((bodies[j]->getPosition() - bodies[i]->getPosition()),2)) << std::endl;
                        // }

                        if(bodies[i]->collidesWith(bodies[j]->getPosition(), bodies[j]->getSize())){
                            if(magnitude(bodies[i]->getVelocity()) + magnitude(bodies[j]->getVelocity()) < 75.f){
                                bodies[i]->addMass(bodies[j]->getMass());
                                bodies[i]->setSize(sqrt(pow(bodies[i]->getSize(), 2) + pow(bodies[j]->getSize(), 2)));
                                bodies.erase(bodies.begin()+j);
                                j--;
                            }else{
                                // https://en.wikipedia.org/wiki/Elastic_collision#Two-dimensional
                                float m1 = bodies[i]->getMass();
                                float m2 = bodies[j]->getMass();
                                float v1 = magnitude(bodies[i]->getVelocity());
                                float v2 = magnitude(bodies[j]->getVelocity());
                                float theta1 = angleRadians(bodies[i]->getVelocity());
                                float theta2 = angleRadians(bodies[j]->getVelocity());
                                float phi = angleRadians(bodies[j]->getPosition() - bodies[i]->getPosition());
                                bodies[i]->setVelocity(sf::Vector2f(
                                    ( ( ( ( v1 * cos(theta1 - phi) * (m1-m2) ) + ( 2.f * m2 * v2 * cos(theta2 - phi) ) ) / (m1 + m2) ) * cos(phi) ) + ( v1 * sin(theta1 - phi) * cos(phi + (Definition::pi/2.f)) ),
                                    ( ( ( ( v1 * cos(theta1 - phi) * (m1-m2) ) + ( 2.f * m2 * v2 * cos(theta2 - phi) ) ) / (m1 + m2) ) * sin(phi) ) + ( v1 * sin(theta1 - phi) * sin(phi + (Definition::pi/2.f)) )
                                ) * 0.825);
                                bodies[j]->setVelocity(sf::Vector2f(
                                    ( ( ( ( v2 * cos(theta2 - phi) * (m2-m1) ) + ( 2.f * m1 * v1 * cos(theta1 - phi) ) ) / (m2 + m1) ) * cos(phi) ) + ( v2 * sin(theta2 - phi) * cos(phi + (Definition::pi/2.f)) ),
                                    ( ( ( ( v2 * cos(theta2 - phi) * (m2-m1) ) + ( 2.f * m1 * v1 * cos(theta1 - phi) ) ) / (m2 + m1) ) * sin(phi) ) + ( v2 * sin(theta2 - phi) * sin(phi + (Definition::pi/2.f)) )
                                ) * 0.825);
                                bodies[i]->goBack();
                                bodies[j]->goBack();
                            }
                        }
                    }
                }
                bodies[i]->update(delta);
                if(distance(bodies[i]->getPosition(), engine->settings->getScreenCenter()) > engine->settings->screenWidth*5){
                    bodies.erase(bodies.begin()+i);
                    i--;
                }
            }
        }

        void draw(float delta){
            for(unsigned int i=0; i<bodies.size(); i++){
                bodies[i]->draw(delta);
            }
        }

        void addBody(std::unique_ptr<Circle_Object> newBody){
            bodies.push_back(std::move(newBody));
        }
    };

} // namespace VeX

#endif // __GRAVITATIONAL_SYSTEM_HPP__
