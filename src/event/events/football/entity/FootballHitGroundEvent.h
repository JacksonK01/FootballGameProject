//
// Created by jkirc on 8/12/2025.
//

#pragma once

#include "../../../Event.h"

class FootballEntity;
class PositionEntity;

struct FootballHitGroundEvent : Event {
    explicit FootballHitGroundEvent(FootballEntity& football, PositionEntity* thrower) : football(football), thrower(thrower) {};
    FootballEntity& football;
    PositionEntity* thrower;
};
