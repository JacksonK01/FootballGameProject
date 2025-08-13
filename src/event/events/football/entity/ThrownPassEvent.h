//
// Created by jkirc on 8/11/2025.
//

#ifndef THROWNPASSEVENT_H
#define THROWNPASSEVENT_H
#include "../../../Event.h"
#include "../../../../scene/football/entity/positions/PositionEntity.h"


struct ThrownPassEvent : Event {
    explicit ThrownPassEvent(PositionEntity& qb, const Vector2D& pos) : qb(qb), pos(pos) {}
    PositionEntity& qb;
    Vector2D pos;
};

#endif //THROWNPASSEVENT_H
