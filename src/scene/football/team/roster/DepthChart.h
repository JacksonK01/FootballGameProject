//
// Created by jkirc on 8/10/2025.
//
#pragma once

#include <map>
#include <vector>

#include "../../util/Position.h"

namespace sf {
    class RenderWindow;
}

class Roster;
class PositionEntity;

//Basically a way to store the starting lineup. Will store pointers or references, this is NOT the actual roster, rather this is the
//order at which players will start.
class DepthChart {
public:
    explicit DepthChart(Roster& roster);
    PositionEntity* getStartingQB();
    //i is used to find which WR, for example i = 0 means WR1
    PositionEntity* getWR(int i);
    PositionEntity* getPosition(Position position, int i);
    std::vector<PositionEntity*>& getOnFieldPlayers() { return onFieldPlayers; }

    void tick(double dt);
    void render(double dt, sf::RenderWindow& window);

private:
    std::map<Position, std::vector<PositionEntity*>> depth = std::map<Position, std::vector<PositionEntity*>>();
    //Whoever is currently on the field, will be decided by a formation
    std::vector<PositionEntity*> onFieldPlayers = std::vector<PositionEntity*>();

    bool doesDepthExist(Position position, int at);
};

