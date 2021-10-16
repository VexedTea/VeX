#ifndef __LOADING_STATE_HPP__
#define __LOADING_STATE_HPP__

#include <thread>
#include <functional>

#include "progress_bar.hpp"

namespace VeX{

    class Loading_State : public State{
    private:
    float & progress;
        std::thread loadingThread;
        std::unique_lock<std::mutex> progressLock;
        Progress_Bar progressBar;
        
    public:
        Loading_State(const std::string & title, float & progress, std::mutex & progressMutex, std::function<void()> progressorFunction);
        
        void init();
        
        void handleInput();
        
        void update(float);
        
        void draw(float);
    };

} // namespace VeX

#endif // __LOADING_STATE_HPP__
