//
// Created by jkirc on 8/20/2025.
//

#pragma once

#include "../../../Event.h"

struct PassCaughtEvent : public Event {
    explicit PassCaughtEvent(PositionEntity* wr, FootballEntity& football) : wr(wr), football(football) {};
    PositionEntity* wr;
    FootballEntity& football;
};
