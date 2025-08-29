//
// Created by jkirc on 8/18/2025.
//

#pragma once

#include <map>
#include <vector>

#include "FormationSlot.h"
#include "../../../../../util/Logger.h"
#include "../../../util/FormationType.h"
#include "../../../util/Position.h"

class DepthChart;
class Vector2D;
class FootballField;

//Like Route class, a custom formation can be created whenever, but there will be presets
class Formation {
public:
    static constexpr int MAX_PLAYERS_ON_FIELD = 11;

    explicit Formation(const FormationType& type): type(type) {}

    void addFormationSlot(const Position& position, const FormationSlot& slot) {
        if (getTotalAmountOfSlots() > MAX_PLAYERS_ON_FIELD) {
            Logger::error("Too many players in a formation", typeid(*this));
        }

        if (formationSlots.contains(position)) {
            formationSlots[position].emplace_back(slot);
        } else {
            formationSlots[position] = std::vector<FormationSlot>();
            formationSlots[position].emplace_back(slot);
        }
    }

    std::map<Position, std::vector<FormationSlot>>& getPlayers() {
        if (getTotalAmountOfSlots() > MAX_PLAYERS_ON_FIELD) {
            Logger::error("Too many players in a formation", typeid(*this));
        }
        return formationSlots;
    }

    //It is not the formation's job to make sure this depth chart is proper.
    void alignPlayers(DepthChart& depthChart, FootballField& field, const Vector2D& origin, const bool& isLeftToRight);

private:
    std::map<Position, std::vector<FormationSlot>> formationSlots = {};
    FormationType type;

    int getTotalAmountOfSlots() const {
        int size = 0;

        for (auto& pair : formationSlots) {
            size += pair.second.size();
        }

        return size;
    }
    Vector2D calculatePosition(const FormationSlot& slot, const FootballField& field, const Vector2D &origin);
};
