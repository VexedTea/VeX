#ifndef __PARTICLE_DEMO_HPP__
#define __PARTICLE_DEMO_HPP__

#include <vector>
#include <memory>

#include "particle.hpp"
// #include "particle_system.hpp"
#include "particle_system_thread.hpp"
#include "engine.hpp"
#include "utilities.hpp"

namespace VeX{

    class Particle_Demo : public State{
    private:
        bool snapToScreenCenter;
        bool circlePaused;
        bool showCenters;
        bool drawParticles;
        bool maxParticleCountReached;
        float circleAngle;
        unsigned int primitiveTypeIndex;
        std::vector<sf::PrimitiveType> primitiveTypes;
        std::vector<std::unique_ptr<Particle_System_Thread>> particleSystems;
    public:
        Particle_Demo(bool snapToScreenCenter=true, bool circlePaused=false);

        void init();

        void handleInput();

        void update(float delta);

        void draw(float delta);

        void pause()override;

        void resume()override;

        void stop()override;
    };

} // namespace VeX

#endif // __PARTICLE_DEMO_HPP__
