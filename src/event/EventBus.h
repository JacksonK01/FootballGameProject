//
// Created by jkirc on 8/10/2025.
//

#pragma once

#include <functional>
#include <map>
#include <string>

#include "Emitter.h"
#include "Event.h"
#include "../util/Demangler.h"
#include "../util/Logger.h"


//This houses the events. Events will be able to prevent coupling.
class EventBus {
public:
    //So I don't have to retype the type every time
    using Listener = std::function<void(Event&)>;

    //When calling this method, use the event struct desired as the generic.
    //This is the rvalue method.
    template<typename EventType>
    void subscribe(std::function<void(EventType&)>&& listener) {
        const std::string eventName = Demangler::demangle(typeid(EventType).name());
        Logger::initialize("(Created Event): " + eventName, typeid(*this));

        //Have to cast the event type, and move memory of listener into castedListener due to it being an rvalue.
        auto castedListener = [listener = std::move(listener)](Event& event) {
            listener(static_cast<EventType&>(event));
        };

        listeners[eventName].emplace_back(castedListener);
    }

    //Overload subscribe method for lvalues.
    //Warning:
    //Do note when you std::move listener here, the original variable will no longer work. The eventbus will own that function after passing it
    //through this method. Any lvalue that gets passed into this function will no longer be yours.
    template<typename EventType>
    void subscribe(std::function<void(EventType&)>& listener) {
        subscribe(std::move(listener));
    }

    //This emits every instance of the given event.
    void emit(Event& event) {
        const std::string eventName = Demangler::demangle(typeid(event).name());
        Logger::log("(Emitting Event): " + eventName, typeid(*this));

        for (Listener& listener : listeners[eventName]) {
            listener(event);
            event.callbacks++;
        }

        Logger::log("(" + eventName + " Callbacks): "  + std::to_string(event.callbacks), typeid(*this));
    }

    //Emitter is purely for objects that are not allowed to subscribe events but can emit them.
    Emitter& getEmitterInstance() { return this->emitter; }

private:
    std::map<std::string, std::vector<Listener>> listeners;
    //This is to hand out. Stored so it's not put out of scope in memory.
    Emitter emitter = Emitter([this](Event& e) { this->emit(e); });
};
