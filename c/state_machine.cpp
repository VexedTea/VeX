#include "../h/state_machine.hpp"

namespace VeX{

    void State_Machine::addState(State_Ptr state, bool replacing){
        isAdding = true;
        isReplacing = replacing;
        newState = std::move(state);
    }

    void State_Machine::removeState(){
        isRemoving = true;
    }

    bool State_Machine::processStateChanges(){
        bool didNotRemove = true;
        if(isRemoving && !statesStack.empty()){
            statesStack.pop();
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
                }else{
                    statesStack.top()->pause();
                }
            }
            statesStack.push(std::move(newState));
            statesStack.top()->init();
            isAdding = false;
            //printstatesStack();
        }
        return didNotRemove;
    }

    State_Ptr & State_Machine::getActiveState(){
        return statesStack.top();
    }

}
