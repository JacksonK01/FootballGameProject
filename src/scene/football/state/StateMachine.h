//
// Created by jkirc on 8/13/2025.
//

#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <memory>

#include "IState.h"
#include "generic/IdleState.h"

//Probably won't need
template<typename T>
class StateMachine {
    virtual ~StateMachine() = default;

    explicit StateMachine(T& owner) : owner(owner), currentState(nullptr) {
        currentState = std::make_unique<IdleState>();
    }

    void changeState(IState* state) {
        if (currentState) {
            currentState->onExit();
            delete currentState;
        }

        currentState = std::unique_ptr<IState>(state);
        currentState->onEnter();
    }

    void tick(double dt) {
        if (currentState) {
            currentState->onTick(dt);
        }
    }

private:
    T& owner;
    std::unique_ptr<IState> currentState;
};

#endif //STATEMACHINE_H
