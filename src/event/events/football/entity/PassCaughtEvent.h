//
// Created by jkirc on 8/20/2025.
//

#ifndef PASSCAUGHTEVENT_H
#define PASSCAUGHTEVENT_H
#include "../../../Event.h"
#include "../../../../scene/football/entity/positions/PositionEntity.h"

struct PassCaughtEvent : public Event {
    explicit PassCaughtEvent(PositionEntity* wr, FootballEntity& football) : wr(wr), football(football) {};
    PositionEntity* wr;
    FootballEntity& football;
};

#endif //PASSCAUGHTEVENT_H
