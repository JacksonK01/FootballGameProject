//
// Created by jkirc on 8/26/2025.
//

#include "DepthChart.h"
#include "../../team/roster/Roster.h"
#include "../../entity/positions/PositionEntity.h"

DepthChart::DepthChart(Roster &roster) {
    //This is just a test, since I know what's on the default roster

    for (std::unique_ptr<PositionEntity>& player: roster.getEntireRoster()) {
        PositionEntity* p_player = player.get();
        depth[p_player->getPosition()].emplace_back(p_player);
    }
};

PositionEntity *DepthChart::getStartingQB() {
    //TODO create a list of constants for abbrevations
    return depth[QB][0];
}

PositionEntity *DepthChart::getWR(int i)  {
    if (0 < i && i < depth[WR].size()) {
        Logger::error("This WR doesn't exist", typeid(*this));
    }
    return depth[WR][i];
}



