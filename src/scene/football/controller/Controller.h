//
// Created by jkirc on 8/10/2025.
//

#pragma once

#include "../entity/positions/PositionEntity.h"
#include "../field/FootballField.h"

//This is the base class for who or what is controlling a Position Entity.
//The controller will be owned by the entity, generally speaking, the controller will be owned by the entity, then
//controller managers will grab each controller and run them itself.

//TODO
class Controller {
public:
    virtual ~Controller() = default;

    virtual void tick(double dt, PositionEntity& user, FootballField& field) = 0;

};
