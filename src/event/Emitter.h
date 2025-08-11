//
// Created by jkirc on 8/11/2025.
//

#ifndef EMITTER_H
#define EMITTER_H
#include "Event.h"


//This will be used to be passed down to objects that can't register events, but can emit them.
class Emitter {
public:
    using EmitFunc = std::function<void(Event&)>;
    //emitter function has to use std::move to ensure it's properly stored due to the value being passed being a local variable in EventBus.
    //Double & means rvalues only. Aka temporary objects only
    explicit Emitter(EmitFunc&& emitter) : emitter(std::move(emitter)) {}

    void emit(Event& event) const { this->emitter(event); }
private:
    EmitFunc emitter;
};

#endif //EMITTER_H
