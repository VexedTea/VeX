#ifndef __STATE_MACHINE_HPP__
#define __STATE_MACHINE_HPP__

#include <memory>
#include <stack>
#include <iostream>

#include "state.hpp"

namespace VeX{

    using StatePtr = std::unique_ptr<State>;

    class State_Machine{
    private:
        std::stack<StatePtr> statesStack;
        StatePtr newState;
        bool isRemoving;
        bool isAdding;
        bool isReplacing;
    public:
        void addState(StatePtr state, bool replacing){
            isAdding = true;
            isReplacing = replacing;
            newState = std::move(state);
        }

        void removeState(){
            isRemoving = true;
        }

        void processStateChanges(){
            if(isRemoving && !statesStack.empty()){
                statesStack.pop();
                if(!statesStack.empty()){
                    statesStack.top()->resume();
                }
                isRemoving = false;
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
        }

        StatePtr & getActiveState(){
            return statesStack.top();
        }

        //The below is borked for now :(
        // void printstatesStack(){ //Yoinked function from (edited) https://www.geeksforgeeks.org/print-stack-elements-from-bottom-to-top/
        //     std::cout << "Current State stack: ";
        //     printstatesStackRecursion();
        //     std::cout << " end.\n";
        // }

        // void printstatesStackRecursion(int depth=0){ //Yoinked function from (edited) https://www.geeksforgeeks.org/print-stack-elements-from-bottom-to-top/
        //     // If stack is empty then return
        //     if (statesStack.empty()){
        //         return;
        //     }
        
        //     StatePtr state = statesStack.top();
        
        //     // Pop the top element of the stack
        //     statesStack.pop();
        
        //     // Recursively call the function PrintStack
        //     printstatesStackRecursion(depth++);
        
        //     // Print the stack element starting
        //     // from the bottom
        //     std::cout << depth << ". "<< typeid(state).name() << ";  ";
        
        //     // Push the same element onto the stack
        //     // to preserve the order
        //     statesStack.push(state);
        // }
    };

}

#endif // __STATE_MACHINE_HPP__
