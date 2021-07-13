#ifndef __GRAVITATIONAL_SYSTEM_HPP__
#define __GRAVITATIONAL_SYSTEM_HPP__

#include "utilities.hpp"
#include "circle_object.hpp"

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
                            float m1 = bodies[i]->getMass();    //https://en.wikipedia.org/wiki/Elastic_collision
                            float m2 = bodies[j]->getMass();
                            sf::Vector2f u1 = bodies[i]->getVelocity();
                            sf::Vector2f u2 = bodies[j]->getVelocity();
                            bodies[i]->setVelocity((((m1-m2)/(m1+m2))*u1) + (((2*m2)/(m1+m2))*u2));
                            bodies[j]->setVelocity((((2*m2)/(m1+m2))*u1) + (((m1-m2)/(m1+m2))*u2));
                        }
                    }
                }
                bodies[i]->update(delta);
                if(distance(bodies[i]->getPosition(), engine->settings->getScreenCenter()) > engine->settings->screenWidth*10.f){
                    std::cout << bodies[i]->getPosition() << std::endl;
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
            std::cout << "Gravitational_System addBody" << std::endl;
            bodies.push_back(std::move(newBody));
        }
    };

} // namespace VeX

#endif // __GRAVITATIONAL_SYSTEM_HPP__
