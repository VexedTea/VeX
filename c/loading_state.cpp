#include "../h/loading_state.hpp"

namespace VeX{

    Loading_State::Loading_State(const std::string & title, float & progress, std::mutex & progressMutex, std::function<void()> progressorFunction):
        progress(progress),
        loadingThread(progressorFunction),
        progressLock(progressMutex, std::defer_lock),
        progressBar(title, {10.f,10.f}, {int(engine->settings->screenWidth)-20,100}, 10.f, Definition::vexGradient)
    {
        //std::cout << "Loading_State constructor" << std::endl;
    }
    
    void Loading_State::init(){
        //std::cout << "Loading_State init" << std::endl;
    }
    
    void Loading_State::handleInput(){
        //Handle ur input
        
        sf::Event event;
        while (engine->window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            engine->window.close();
        }
    }
    
    void Loading_State::update(float){
        //std::cout << "Loading_State update" << std::endl;
        progressLock.lock();
        //std::cout << "[main thread] progress: " << progress << std::endl;
        if(progress >= 1.f){
            progressBar.setProgress(1.f);
            progressLock.unlock();
            engine->removeState();
            loadingThread.join();
        }else{
            progressBar.setProgress(progress);
            progressLock.unlock();
        }
    }
    
    void Loading_State::draw(float){
        progressBar.draw();
        
        engine->window.display();
    }

} // namespace VeX
