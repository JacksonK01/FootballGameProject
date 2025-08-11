//
// Created by jkirc on 8/10/2025.
//

#ifndef POSITIONENTITY_H
#define POSITIONENTITY_H
#include "../Entity.h"
#include "rating/Ratings.h"

//This will be the base class to represent a position as an entity. These entities will be built to be controlled by a player or an AI. Will be the
//base class for positions within football I.E. QB, RB, WR, CB.
//Will have base attributes like Stamina, Strength, Awareness, and ETC
class PositionEntity : public Entity {
public:
    PositionEntity(Emitter& emitter) : emitter(emitter) {};
    //Will become useful, example: A quarterback would return "QB"
    virtual const std::string getPositionAbbreviation() = 0;

    //For inputs from a player controller
    virtual void onMouseClicked(const Vector2D pos) = 0;
    virtual void onDirectionalInput(const Vector2D direction) = 0;

protected:
    Rating rating;
    Emitter& emitter;
};

#endif //POSITIONENTITY_H
