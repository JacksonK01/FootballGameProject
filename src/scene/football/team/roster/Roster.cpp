//
// Created by jkirc on 8/26/2025.
//

#include "Roster.h"

Roster::Roster(Emitter &emitter)  {
    addPlayer(new PositionEntity(emitter, QB));

    addPlayer(new PositionEntity(emitter, WR));
};

bool Roster::addPlayer(PositionEntity *player) {
    if (getRosterSize() < MAX_ROSTER_SIZE) {
        entireRoster.emplace_back(std::unique_ptr<PositionEntity>(player));
        return true;
    }

    return false;
}

