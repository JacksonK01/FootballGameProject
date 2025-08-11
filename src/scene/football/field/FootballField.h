//
// Created by jkirc on 8/10/2025.
//

#ifndef FOOTBALLFIELD_H
#define FOOTBALLFIELD_H
#include "../../../event/events/ThrownPassEvent.h"
#include "../entity/positions/QB/QBEntity.h"
#include "../team/Team.h"
#include "SFML/Graphics/RenderWindow.hpp"

//Class for storing who's on the field, who is where, houses each player in one place.
//Possibly should house interaction logic between players? Will decide later.
class FootballField {
public:
    explicit FootballField(EventBus& eventBus): team1(eventBus), team2(eventBus) {
        registerEvents(eventBus);
    };

    void tick(double dt) {
        team1.getDepthChart().getStartingQB()->tick(dt);
    };

    void render(double dt, sf::RenderWindow& window) {
        team1.getDepthChart().getStartingQB()->render(dt, window);
    };

    //TODO this will need to be replaced with getTeamOffense and getTeamDefense.
    Team& getTeam1() { return team1; }

private:
    Team team1;
    Team team2;

    void registerEvents(EventBus& eventBus) {
        //Using this in a lambda capture gives a POINTER of the object. Feels like pointers have no standard in C++, imo should be able to do
        //something like *this to de-reference and pass a reference into the lambda. If you want to capture all variables used in a lambda
        //you can do [&]() {};
        //Lambdas just have their own rules for captures :|
        eventBus.subscribe<ThrownPassEvent>([this](ThrownPassEvent& event) {
            Logger::warn("We IN", typeid(*this));
        });
    }
};

#endif //FOOTBALLFIELD_H
