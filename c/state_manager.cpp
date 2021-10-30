#include "../h/state_manager.hpp"

namespace VeX{

    void State_Manager::addState(State_Ptr state, bool replacing){
        isAdding = true;
        isReplacing = replacing;
        newState = std::move(state);
    }

    void State_Manager::removeState(){
        isRemoving = true;
    }

    bool State_Manager::processStateChanges(){
        bool didNotRemove = true;
        if(isRemoving && !statesStack.empty()){
            statesStack.pop();
            keybinds.pop();
            if(!statesStack.empty()){
                statesStack.top()->resume();
            }
            isRemoving = false;
            didNotRemove = false;
        }
        if(isAdding){
            if(!statesStack.empty()){
                if(isReplacing){
                    statesStack.pop();
                    keybinds.pop();
                }else{
                    statesStack.top()->pause();
                }
            }
            statesStack.push(std::move(newState));
            keybinds.push(std::map<std::string, std::unique_ptr<Keybind>>());
            statesStack.top()->init();
            isAdding = false;
            //printstatesStack();
        }
        return didNotRemove;
    }

    State_Ptr & State_Manager::getActiveState(){
        return statesStack.top();
    }

}
