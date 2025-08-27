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
    doesDepthExist(WR, i);
    return depth[WR][i];
}

PositionEntity *DepthChart::getPosition(Position position, int i) {
    doesDepthExist(position, i);
    return depth[position][i];
}

bool DepthChart::doesDepthExist(Position position, int at) {
    if (0 <= at && at < depth[position].size()) {
        return true;
    }

    Logger::error("This depth doesn't exist", typeid(*this));
    return true;
}

void DepthChart::tick(double dt) {

    for (auto* entity : onFieldPlayers) {
        entity->tick(dt);
    }

}

void DepthChart::render(double dt, sf::RenderWindow &window) {

    for (auto* entity : onFieldPlayers) {
        entity->render(dt, window);
    }

}







