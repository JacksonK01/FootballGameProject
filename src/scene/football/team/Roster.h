//
// Created by jkirc on 8/10/2025.
//

#ifndef ROSTER_H
#define ROSTER_H
#include <vector>

#include "../entity/positions/PositionEntity.h"
#include "../entity/positions/QB/QBEntity.h"

//Object that stores every player on a team. This is not meant to store the order they start in, just who is on what team.
//This is where entities will be created, and then possibly written to I/O.
//Depending on how this works in the future, maybe just make team store a list of every player and call that roster.
class Roster {
public:
    static constexpr int MAX_ROSTER_SIZE = 53;

    Roster(Emitter& emitter) {
        addPlayer(new QBEntity(emitter));
    };

    bool addPlayer(PositionEntity* player) {
        if (getRosterSize() < MAX_ROSTER_SIZE) {
            entireRoster.emplace_back(std::unique_ptr<PositionEntity>(player));
            return true;
        }

        return false;
    }

    int getRosterSize() const {
        return this->entireRoster.size();
    }

    std::vector<std::unique_ptr<PositionEntity>>& getEntireRoster() {
        return entireRoster;
    }

private:
    //Stores std::unique_ptr<PositionEntity> instead of raw pointer since this object is the OWNER of the position entities in the game.
    std::vector<std::unique_ptr<PositionEntity>> entireRoster = std::vector<std::unique_ptr<PositionEntity>>();
};


#endif //ROSTER_H
