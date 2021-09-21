#ifndef __VERTEX_PARTICLE_SYSTEM_HPP__
#define __VERTEX_PARTICLE_SYSTEM_HPP__

#include "object.hpp"
#include "vertex_particle.hpp"

namespace VeX{

    class Vertex_Particle_System : public Object{
    protected:
        sf::CircleShape centerPoint;
        sf::VertexArray vertices;
        std::vector<Vertex_Particle_Ptr> particles;
    private:
        
    public:
        Vertex_Particle_System(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
            Object(position, velocity, mass, motionDampening),
            centerPoint(5.f),
            vertices(sf::PrimitiveType::Points)
        {
            centerPoint.setOrigin({5.f, 5.f});//sf::Sprite centerPoint;
        }

        Vertex_Particle_System(const sf::Vector2f & position, const sf::Vector2f & motionDampening):
            Vertex_Particle_System(position, {0,0}, 0.f, motionDampening)
        {}

        Vertex_Particle_System(const sf::Vector2f & position):
            Vertex_Particle_System(position, {0,0}, 0.f, {0,0})
        {}

        Vertex_Particle_System():
            Vertex_Particle_System({0,0}, {0,0}, 0.f, {0,0})
        {}

        virtual void draw(float){
            if(!hidden) engine->window.draw(vertices);
        }

        void drawCenterPoint(){
            centerPoint.setPosition(position);
            engine->window.draw(centerPoint);
        }

        virtual void update(float delta)override{
            for(unsigned int i=0; i<particles.size(); i++){
                particles[i]->gravTo(position, delta);
                particles[i]->update(delta);
                vertices[i].position = particles[i]->getPosition();
                vertices[i].color = particles[i]->getColor();
            }
        }

        void addParticle(Vertex_Particle_Ptr particle){
            vertices.append(sf::Vertex(particle->getPosition(), particle->getColor()));
            particles.push_back(std::move(particle));
        }

        void removeOldestParticle(){
            if(particles.size() > 0){
                particles.erase(particles.begin());
                vertices.resize(particles.size());
            }
        }

        void setPrimitiveType(const sf::PrimitiveType & type){
            vertices.setPrimitiveType(type);
        }
    };

} // namespace VeX

#endif // __VERTEX_PARTICLE_SYSTEM_HPP__
