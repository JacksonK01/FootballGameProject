//
// Created by jkirc on 8/10/2025.
//
#pragma once

#include <map>
#include <vector>

#include "../../util/Position.h"

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
private:
    std::map<Position, std::vector<PositionEntity*>> depth = std::map<Position, std::vector<PositionEntity*>>();
};

