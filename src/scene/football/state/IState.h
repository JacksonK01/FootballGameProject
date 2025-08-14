//
// Created by jkirc on 8/13/2025.
//

#ifndef ISTATE_H
#define ISTATE_H

//Interface for each possible state
class IState {
public:
    virtual ~IState() = default;
    virtual void onEnter() = 0;
    virtual void onTick(double dt) = 0;
    virtual void onExit() = 0;
};

#endif //ISTATE_H
