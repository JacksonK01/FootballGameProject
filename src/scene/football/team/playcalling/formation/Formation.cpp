//
// Created by jkirc on 8/18/2025.
//

#include "Formation.h"

#include "../../../team/roster/DepthChart.h"
#include "../../../../../util/math/Vector2D.h"
#include "../../../entity/positions/PositionEntity.h"
#include "../../../field/FootballField.h"

//Left to right is the direction the team is moving in
void Formation::alignPlayers(DepthChart &depthChart, FootballField& field, const Vector2D &origin, const bool& isLeftToRight) {
    auto& onField = depthChart.getOnFieldPlayers();
    onField.clear();

    for (auto& pair : formationSlots) {
        const Position& position = pair.first;
        std::vector<FormationSlot>& slots = pair.second;

        for (int i = 0; i < slots.size(); i++) {
            PositionEntity* entity = depthChart.getPosition(position, i);
            Vector2D pos = calculatePosition(slots[i], field, origin);

            if (isLeftToRight) {
                pos = pos.multiply(-1);
            }

            entity->setX(pos.getX());
            entity->setY(pos.getY());

            onField.emplace_back(entity);
        }
    }
}

Vector2D Formation::calculatePosition(const FormationSlot &slot, const FootballField &field, const Vector2D &origin) {
    double x = 0;
    double y = 0;

    //This is the y axis
    constexpr int fieldW = FieldConstants::FIELD_WIDTH_YARDS;

    //For now, this is hard coded values
    //TODO make this scale with origin
    switch (slot.horizontal) {
        //Left side alignment
        case HorizontalAlignment::LEFT_SIDELINE: y = 2; break;
        case HorizontalAlignment::LEFT_NUMBERS: y = -(fieldW / 4); break;
        case HorizontalAlignment::LEFT_SLOT: y = -(fieldW / 2); break;
        //Right side alignments
        case HorizontalAlignment::RIGHT_SIDELINE: y = fieldW - 2; break;
        case HorizontalAlignment::RIGHT_NUMBERS: y = fieldW - (fieldW / 4); break;
        case HorizontalAlignment::RIGHT_SLOT: y = fieldW - (fieldW / 2); break;

        default: break;
    }

    switch (slot.depth) {
        case DepthAlignment::SLOT: x = -1; break;
        case DepthAlignment::QB_GUN: x = -5; break;
        default: break;
    }

    Logger::log("x: " + std::to_string(x) + " y: " + std::to_string(y));


    return Vector2D(x, y) + slot.offset + origin;
}
