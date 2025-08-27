//
// Created by jkirc on 8/10/2025.
//

#pragma once

#include "roster/DepthChart.h"
#include "roster/Roster.h"

class EventBus;

//Will hold the depth chart for the team, as well as team name, maybe stats?, and the primary and secondary color of the team.
class Team {
public:
    explicit Team(EventBus& eventBus);

    DepthChart& getDepthChart() { return this->depthChart; }
    //gets called on when it's time to get a play up and going.
    void playcall();

    void tick(double dt);
    void render(double dt, sf::RenderWindow& window);

private:
    Roster roster;
    DepthChart depthChart;
    double currentYardOnField = 0;
};
