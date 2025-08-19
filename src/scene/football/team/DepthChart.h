//
// Created by jkirc on 8/10/2025.
//

#ifndef DEPTHCHART_H
#define DEPTHCHART_H
#include <map>

#include "Roster.h"

//Basically a way to store the starting lineup. Will store pointers or references, this is NOT the actual roster, rather this is the
//order at which players will start.
class DepthChart {
public:
    explicit DepthChart(Roster& roster) {
        //This is just a test, since I know what's on the default roster

        for (std::unique_ptr<PositionEntity>& player: roster.getEntireRoster()) {
            PositionEntity* p_player = player.get();
            depth[p_player->getPosition()].emplace_back(p_player);
        }
    };

    PositionEntity* getStartingQB() {
        //TODO create a list of constants for abbrevations
        return depth[QB][0];
    }

    //i is used to find which WR, for example i = 0 means WR1
    PositionEntity* getWR(int i) {
        if (0 <= i && i < 3) {
            Logger::error("This WR doesn't exist", typeid(*this));
        }
        return depth[WR][i];
    }

private:
    std::map<Position, std::vector<PositionEntity*>> depth = std::map<Position, std::vector<PositionEntity*>>();
};

#endif //DEPTHCHART_H
