//
// Created by jkirc on 8/10/2025.
//

#ifndef TEAM_H
#define TEAM_H
#include "DepthChart.h"
#include "Roster.h"
#include "../../../event/Emitter.h"

//Will hold the depth chart for the team, as well as team name, maybe stats?, and the primary and secondary color of the team.
class Team {
public:
    Team(EventBus& eventBus)
    : roster(eventBus.getEmitterInstance()),
      depthChart(roster)
    {}

    DepthChart& getDepthChart() { return this->depthChart; }
private:
    Roster roster;
    DepthChart depthChart;
};

#endif //TEAM_H
