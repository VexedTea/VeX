#ifndef __LOADING_STATE_HPP__
#define __LOADING_STATE_HPP__

#include "progress_bar.hpp"

namespace VeX{

    class Loading_State : public State{
    private:
    float & progress;
        std::thread loadingThread;
        std::unique_lock<std::mutex> progressLock;
        Progress_Bar progressBar;
        
    public:
        Loading_State(const std::string & title, float & progress, std::mutex & progressMutex, std::function<void()> progressorFunction):
            progress(progress),
            loadingThread(progressorFunction),
            progressLock(progressMutex, std::defer_lock),
            progressBar(title, {10.f,10.f}, {int(engine->settings->screenWidth)-20,100}, 10.f, Definition::vexGradient)
        {
            //std::cout << "Loading_State constructor" << std::endl;
        }
        
        void init(){
            //std::cout << "Loading_State init" << std::endl;
        }
        
        void handleInput(){
            //Handle ur input
            
            sf::Event event;
            while (engine->window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                engine->window.close();
            }
        }
        
        void update(float){
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
        
        void draw(float){
            progressBar.draw();
            
            engine->window.display();
        }
    };

} // namespace VeX

#endif // __LOADING_STATE_HPP__
