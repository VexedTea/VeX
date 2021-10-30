#ifndef __STATE_MANAGER_HPP__
#define __STATE_MANAGER_HPP__

#include <memory>
#include <stack>
#include <iostream>

#include "state.hpp"
#include "input_manager.hpp"

namespace VeX{

    using State_Ptr = std::unique_ptr<State>;

    class State_Manager : public Input_Manager{
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

#endif // __STATE_MANAGER_HPP__
