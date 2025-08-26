//
// Created by jkirc on 8/11/2025.
//

#pragma once

#include "../../../Event.h"

struct ThrownPassEvent : Event {
    explicit ThrownPassEvent(PositionEntity& qb, FootballEntity& football, const Vector2D& pos) : qb(qb), football(football), pos(pos) {}
    PositionEntity& qb;
    FootballEntity& football;
    Vector2D pos;
};

