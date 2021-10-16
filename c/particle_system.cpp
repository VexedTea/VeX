#include "../h/particle_system.hpp"

namespace VeX{

    Particle_System::Particle_System(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening):
        Object(position, velocity, mass, motionDampening),
        centerPoint(5.f),
        vertices(sf::PrimitiveType::Points)
    {
        centerPoint.setOrigin({5.f, 5.f});//sf::Sprite centerPoint;
    }

    Particle_System::Particle_System(const sf::Vector2f & position, const sf::Vector2f & motionDampening):
        Particle_System(position, {0,0}, 0.f, motionDampening)
    {}

    Particle_System::Particle_System(const sf::Vector2f & position):
        Particle_System(position, {0,0}, 0.f, {0,0})
    {}

    Particle_System::Particle_System():
        Particle_System({0,0}, {0,0}, 0.f, {0,0})
    {}

    void Particle_System::draw(float){
        if(!hidden) engine->window.draw(vertices);
    }

    void Particle_System::drawCenterPoint(){
        centerPoint.setPosition(position);
        engine->window.draw(centerPoint);
    }

    void Particle_System::update(float delta){
        for(unsigned int i=0; i<particles.size(); i++){
            particles[i]->gravTo(position, delta);
            particles[i]->update(delta);
            vertices[i].position = particles[i]->getPosition();
            vertices[i].color = particles[i]->getColor();
        }
    }

    void Particle_System::addParticle(Particle_Ptr particle){
        vertices.append(sf::Vertex(particle->getPosition(), particle->getColor()));
        particles.push_back(std::move(particle));
    }

    void Particle_System::removeOldestParticle(){
        if(particles.size() > 0){
            particles.erase(particles.begin());
            vertices.resize(particles.size());
        }
    }

    void Particle_System::setPrimitiveType(const sf::PrimitiveType & type){
        vertices.setPrimitiveType(type);
    }

} // namespace VeX
