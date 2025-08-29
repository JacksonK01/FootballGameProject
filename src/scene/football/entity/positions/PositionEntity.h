//
// Created by jkirc on 8/10/2025.
//

#pragma once

#include "../Entity.h"
#include "PositionEntityState.h"
#include "../../util/Position.h"
#include "rating/Ratings.h"
#include "SFML/Graphics/Texture.hpp"
#include "../../route/Route.h"

class Emitter;
class FootballEntity;

//This will be the base class to represent a position as an entity. These entities will be built to be controlled by a player or an AI. Will be the
//base class for positions within football I.E. QB, RB, WR, CB.
//Will have base attributes like Stamina, Strength, Awareness, and ETC
//Any position will be able to do anything.
class PositionEntity : public Entity {
public:
    explicit PositionEntity(Emitter& emitter, Position primaryPosition);

    //For inputs from a player controller
    void onMouseClicked(const Vector2D& pos);

    void onDirectionalInput(const Vector2D& direction);

    //Returns true if football is successfully removed
    bool removeFootball();

    //returns true if football can be given.
    bool giveFootball(FootballEntity* football);

    //returns true if have football
    bool doesHaveFootball() { return this->football; }

    Rating getRatings() { return rating; }

    Position getPosition() { return primaryPosition; }

    Vector2D getPos() { return {x, y}; }

    void setState(const PositionEntityState& state) { this->state = state; }

    void runRoute(const Route& route);

    void tick(double dt) override;

    void render(double dt, sf::RenderWindow &window) override;

protected:
    //Although a position entity can play and do whatever needed, they still need to know what they are.
    Position primaryPosition;
    Rating rating;
    Emitter& emitter;
    std::optional<Route> route;
    PositionEntityState state = IDLE;

    //Generic texture
    sf::Texture idle;
    //Qb texture
    sf::Texture dropbackTexture;

    //Meant for only internals
    FootballEntity& getFootball();

private:
    FootballEntity* football = nullptr;
    //TODO delete routeStartPos, it's a dummy value for run route to know where the entity started
    Vector2D* routeStartPos = nullptr;

    //TODO delete routeOrigin, used to know where to keep rendering the route
    Vector2D* routeOrigin = nullptr;

    void idleState();

    void readyToThrow();

    void runRoute(double dt);
};
