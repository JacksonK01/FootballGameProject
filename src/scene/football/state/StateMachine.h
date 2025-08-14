//
// Created by jkirc on 8/13/2025.
//

#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "IState.h"
#include "generic/IdleState.h"

template<typename T>
class StateMachine {
    virtual ~StateMachine() = default;

    explicit StateMachine(T& owner) : owner(owner), currentState(nullptr) {
        currentState = new IdleState();
    }

    void changeState(IState* state) {
        if (currentState) {
            currentState->onExit();
            delete currentState;
        }

        currentState = state;
        currentState->onEnter();
    }

    void tick(double dt) {
        if (currentState) {
            currentState->onTick(dt);
        }
    }

private:
    T& owner;
    IState* currentState;
};

#endif //STATEMACHINE_H
