//
// Created by jkirc on 8/13/2025.
//

#ifndef IDLE_H
#define IDLE_H
#include "../IState.h"

//Dummy state
class IdleState : public IState {
    void onEnter() override {

    };

    void onTick(double dt) override {

    };

    void onExit() override {

    };
};

#endif //IDLE_H
