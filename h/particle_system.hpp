#ifndef __PARTICLE_SYSTEM_HPP__
#define __PARTICLE_SYSTEM_HPP__

#include <vector>
#include <memory>

#include "object.hpp"
#include "particle.hpp"
#include "engine.hpp"

namespace VeX{

    class Particle_System : public Object{
    protected:
        sf::CircleShape centerPoint;
        std::vector<Particle_Ptr> particles;
    public:
        Particle_System(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            Object(position, velocity, mass, motionDampening),
            centerPoint(5.f)
            //particles({})
        {
            centerPoint.setOrigin({5.f, 5.f});sf::Sprite centerPoint;
        }

        Particle_System(const sf::Vector2f & position, const sf::Vector2f & motionDampening):
            Particle_System(position, {0,0}, 0.f, motionDampening)
        {}

        Particle_System(const sf::Vector2f & position):
            Particle_System(position, {0,0}, 0.f, {0,0})
        {}

        Particle_System():
            Particle_System({0,0}, {0,0}, 0.f, {0,0})
        {}

        virtual void draw(float delta){
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->draw(delta);
            }
        }

        void drawCenterPoint(){
            centerPoint.setPosition(position);
            engine->window.draw(centerPoint);
        }

        virtual void update(float delta)override{
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->gravTo(position, delta);
                particles[i]->update(delta);
            }
        }

        void addParticle(std::unique_ptr<Particle> particle){
            particles.push_back(std::move(particle));
        }

        void hide()override{
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->hide();
            }
        }

        void removeOldestParticle(){
            if(particles.size() > 0){
                particles.erase(particles.begin());
            }
        }
    };

} // namespace VeX

#endif // __PARTICLE_SYSTEM_HPP__
