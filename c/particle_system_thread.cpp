#include "../h/particle_system_thread.hpp"

namespace VeX{

    Particle_System_Thread::Particle_System_Thread():
        updateFlag(false),
        updateDoneFlag(false),
        stopFlag(false),
        delta(0.f),
        particleSystem(),
        psMutex()
    {
        psThread = std::thread(&Particle_System_Thread::run, this);
    }

    Particle_System_Thread::~Particle_System_Thread(){
        stopFlag.store(true);
        psThread.join();
    }

    void Particle_System_Thread::run(){
        while(!stopFlag.load()){
            if(updateFlag.load()){
                std::lock_guard<std::mutex> lock(psMutex);
                updateFlag.store(false);
                particleSystem.update(delta.load());
                updateDoneFlag.store(true);
            }
            std::this_thread::yield();
        }
        stopFlag.store(true);
        return;
    }

    void Particle_System_Thread::pause(){
        stopFlag.store(true);
        psThread.join();
    }

    void Particle_System_Thread::resume(){
        psThread = std::thread(&Particle_System_Thread::run, this);
    }

    void Particle_System_Thread::draw(float delta){
        std::lock_guard<std::mutex> lock(psMutex);
        particleSystem.draw(delta); // I am well aware this is being ran in whatever thread calls this function.
    }                               // There is a limitation with SFML where only one thread can access the window at a time, so to be safe, I do all drawing in one thread.

    void Particle_System_Thread::drawCenterPoint(){
        std::lock_guard<std::mutex> lock(psMutex);
        particleSystem.drawCenterPoint();
    }

    void Particle_System_Thread::update(float dt){
        delta.store(dt);
        updateFlag.store(true);
    }

    bool Particle_System_Thread::isUpdateDone(){
        if(updateDoneFlag.load()){
            updateDoneFlag.store(false);
            return true;
        }else{
            return false;
        }
    }

    void Particle_System_Thread::waitForUpdateDone(){
        while(!updateDoneFlag.load()){
            std::this_thread::yield();
        }
        updateDoneFlag.store(false);
    }

    void Particle_System_Thread::addParticle(Particle_Ptr particle){
        std::lock_guard<std::mutex> lock(psMutex);
        particleSystem.addParticle(std::move(particle));
    }

    void Particle_System_Thread::removeOldestParticle(){
        std::lock_guard<std::mutex> lock(psMutex);
        particleSystem.removeOldestParticle();
    }

    void Particle_System_Thread::setPrimitiveType(const sf::PrimitiveType & type){
        std::lock_guard<std::mutex> lock(psMutex);
        particleSystem.setPrimitiveType(type);
    }

    void Particle_System_Thread::setPosition(const sf::Vector2f & newPos){
        std::lock_guard<std::mutex> lock(psMutex);
        particleSystem.setPosition(newPos);
    }

    sf::Vector2f Particle_System_Thread::getPosition(){
        std::lock_guard<std::mutex> lock(psMutex);
        return particleSystem.getPosition();
    }

} // namespace VeX
