//
// Created by jkirc on 8/12/2025.
//

#ifndef FOOTBALLHITGROUNDEVENT_H
#define FOOTBALLHITGROUNDEVENT_H
#include "../../../Event.h"
#include "../../../../scene/football/entity/objects/FootballEntity.h"

struct FootballHitGroundEvent : Event {
    explicit FootballHitGroundEvent(FootballEntity& football, PositionEntity* thrower) : football(football), thrower(thrower) {};
    FootballEntity& football;
    PositionEntity* thrower;
};

#endif //FOOTBALLHITGROUNDEVENT_H
