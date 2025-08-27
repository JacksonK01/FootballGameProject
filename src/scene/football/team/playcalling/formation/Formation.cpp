//
// Created by jkirc on 8/18/2025.
//

#include "Formation.h"

#include "../../../team/roster/DepthChart.h"
#include "../../../../../util/math/Vector2D.h"
#include "../../../entity/positions/PositionEntity.h"

//Left to right is the direction the team is moving in
void Formation::alignPlayers(DepthChart &depthChart, const Vector2D &origin, const bool& isLeftToRight) {
    auto& onField = depthChart.getOnFieldPlayers();
    onField.clear();

    for (auto& pair : formationSlots) {
        const Position& position = pair.first;
        std::vector<FormationSlot>& slots = pair.second;

        for (int i = 0; i < slots.size(); i++) {
            PositionEntity* entity = depthChart.getPosition(position, i);
            Vector2D toAdd = Vector2D(slots[i].x, slots[i].y);

            if (isLeftToRight) {
                toAdd = toAdd.multiply(-1);
            }

            Vector2D pos = origin + toAdd;

            entity->setX(pos.getX());
            entity->setY(pos.getY());

            onField.emplace_back(entity);
        }
    }
}
