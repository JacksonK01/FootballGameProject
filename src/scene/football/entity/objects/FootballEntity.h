//
// Created by jkirc on 8/10/2025.
//

#pragma once

#include "../Entity.h"
#include "SFML/Graphics/Texture.hpp"

class PositionEntity;

//Will be used to represent the actual football itself in game.
//A football's state will modify during a play and be reset once a play is over and the game moves to the next.
class FootballEntity : public Entity {
public:
    FootballEntity();

    void tick(double dt) override;
    void render(double dt, sf::RenderWindow &window) override;

    void isVisible(const bool&& shouldRender) { this->shouldRender = shouldRender; }
    void setDestination(const Vector2D& dest) { this->destination = dest; }
    void initiateThrow() { this->isThrown = true; }
    bool isOnGround() const { return this->isGrounded; }
    void reset();

    void setOwner(PositionEntity* owner) { this->owner = owner; }
    PositionEntity* getOwner();
    bool doesHaveOwner() const { return owner; }

private:
    static constexpr int RANGE_IN_DEGREES = 60;

    double z = 0;

    //TODO fix magic numbers here
    //Starts at -1 for default value.
    //Cached once, gets the total throw distance
    double distanceCache = -1;
    //Tracks how far along the throw you are.
    double traveledDistance = 0;

    //Whoever threw ball
    PositionEntity* owner = nullptr;

    sf::Texture texture;
    Vector2D destination;

    //TODO Build a state machine for this.
    bool isThrown = false;
    bool shouldRender = false;
    bool isGrounded = false;
};
