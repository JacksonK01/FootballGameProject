//
// Created by jkirc on 8/18/2025.
//

#ifndef FORMATION_H
#define FORMATION_H
#include <map>
#include <vector>

#include "FormationSlot.h"
#include "../../../../util/Logger.h"
#include "../../util/FormationType.h"
#include "../../util/Position.h"

class DepthChart;

class Formation {
public:
    static constexpr int MAX_PLAYERS_ON_FIELD = 11;

    explicit Formation(const DepthChart& depth, const FormationType& type): players{}, type(type) {}

    std::map<Position, std::vector<FormationSlot>>& getPlayers() {
        if (players.size() > MAX_PLAYERS_ON_FIELD) {
            Logger::error("Too many players in a formation", typeid(*this));
        }
        return players;
    }

private:
    std::map<Position, std::vector<FormationSlot>> players;
    FormationType type;
};



#endif //FORMATION_H
