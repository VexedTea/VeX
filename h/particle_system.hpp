#ifndef __PARTICLE_SYSTEM_HPP__
#define __PARTICLE_SYSTEM_HPP__

#include "object.hpp"
#include "particle.hpp"

namespace VeX{

    class Particle_System : public Object{
    protected:
        sf::CircleShape centerPoint;
        sf::VertexArray vertices;
        std::vector<Particle_Ptr> particles;
    private:
        
    public:
        Particle_System(const sf::Vector2f & position, const sf::Vector2f & velocity, float mass, const sf::Vector2f & motionDampening);

        Particle_System(const sf::Vector2f & position, const sf::Vector2f & motionDampening);

        Particle_System(const sf::Vector2f & position);

        Particle_System();

        virtual void draw(float, const sf::Shader & shader);

        void drawCenterPoint();

        virtual void update(float delta)override;

        void addParticle(Particle_Ptr particle);

        void removeOldestParticle();

        void setPrimitiveType(const sf::PrimitiveType & type);
    };

} // namespace VeX

#endif // __PARTICLE_SYSTEM_HPP__
