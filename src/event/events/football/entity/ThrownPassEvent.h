//
// Created by jkirc on 8/11/2025.
//

#ifndef THROWNPASSEVENT_H
#define THROWNPASSEVENT_H
#include "../../../Event.h"

class PositionEntity;
class FootballEntity;

struct ThrownPassEvent : Event {
    explicit ThrownPassEvent(PositionEntity& qb, FootballEntity& football, const Vector2D& pos) : qb(qb), football(football), pos(pos) {}
    PositionEntity& qb;
    FootballEntity& football;
    Vector2D pos;
};

#endif //THROWNPASSEVENT_H
