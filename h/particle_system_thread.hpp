#ifndef __PARTICLE_SYSTEM_THREAD_HPP__
#define __PARTICLE_SYSTEM_THREAD_HPP__

#include <thread>
#include <mutex>
#include <atomic>

#include "particle_system.hpp"

namespace VeX{

    class Particle_System_Thread{
    private:
        std::atomic<bool> updateFlag;
        std::atomic<bool> updateDoneFlag;
        std::atomic<bool> stopFlag;
        std::atomic<float> delta;
        Particle_System particleSystem;
        std::mutex psMutex;
        std::thread psThread;
    public:
        Particle_System_Thread();

        ~Particle_System_Thread();

        void run();

        void pause();

        void resume();

        void draw(float delta);

        void drawCenterPoint();

        void update(float delta);

        bool isUpdateDone();

        void waitForUpdateDone();

        void addParticle(Particle_Ptr particle);

        void removeOldestParticle();

        void setPrimitiveType(const sf::PrimitiveType & type);

        void setPosition(const sf::Vector2f & newPos);

        sf::Vector2f getPosition();
    };

} // namespace VeX

#endif // __PARTICLE_SYSTEM_THREAD_HPP__
