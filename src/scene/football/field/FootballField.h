//
// Created by jkirc on 8/10/2025.
//

#pragma once

#include "FieldState.h"
#include "../team/Team.h"
#include "../entity/objects/FootballEntity.h"

namespace sf {
    class RenderWindow;
}

class EventBus;
class PositionEntity;

//Class for storing who's on the field, who is where, houses each player in one place.
//Possibly should house interaction logic between players? Will decide later.
class FootballField {
public:
    explicit FootballField(EventBus& eventBus);

    //Called when space bar input
    //For now will just be a pos reset
    void snapBall();

    void tick(double dt);

    void render(double dt, sf::RenderWindow& window);

    //TODO this will need to be replaced with getTeamOffense and getTeamDefense.
    Team& getTeamOffense() { return team1; }

    Vector2D getPos() const { return {this->x, this->y}; }

    PositionEntity* collisionCheck(const util::Rectangle& hitbox);

private:
    EventBus& eventBus;
    Team team1;
    Team team2;
    FootballEntity football;
    FieldState state = FieldState::SNAP;

    sf::Texture texture;

    double x = 2;
    double y = 2;

    sf::Texture grass;
    sf::Texture boundary;

    void playCallingState(double dt);

    //For when the ball gets snapped
    void snappedBallState(double dt);

    //Using this in a lambda capture gives a POINTER of the object. Feels like pointers have no standard in C++, imo should be able to do
    //something like *this to de-reference and pass a reference into the lambda. If you want to capture all variables used in a lambda
    //you can do [&]() {};
    //Lambdas just have their own rules for captures :|
    void registerEvents(EventBus& eventBus);

    void renderGrassLayer(double dt, sf::RenderWindow& window);

    void renderBoundariesLayer(double dt, sf::RenderWindow& window);
};

