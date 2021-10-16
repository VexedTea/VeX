#ifndef __STATE_MACHINE_HPP__
#define __STATE_MACHINE_HPP__

#include <memory>
#include <stack>
#include <iostream>

#include "state.hpp"

namespace VeX{

    using State_Ptr = std::unique_ptr<State>;

    class State_Machine{
    private:
        std::stack<State_Ptr> statesStack;
        State_Ptr newState;
        bool isRemoving;
        bool isAdding;
        bool isReplacing;
    public:
        void addState(State_Ptr state, bool replacing);

        void removeState();

        bool processStateChanges();

        State_Ptr & getActiveState();
        
    };

}

#endif // __STATE_MACHINE_HPP__
