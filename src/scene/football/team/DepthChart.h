//
// Created by jkirc on 8/10/2025.
//

#ifndef DEPTHCHART_H
#define DEPTHCHART_H
#include <map>

#include "Roster.h"

//Basically a way to store the starting lineup. Will store pointers or references, this is NOT the actual roster, rather this is the
//order at which players will start.
class DepthChart {
public:

    explicit DepthChart(Roster& roster) {
        //This is just a test, since I know currently there's only one player added to the roster.

        PositionEntity* qb = roster.getEntireRoster().at(0).get();
        depth[qb->getPositionAbbreviation()] = qb;
    };

    PositionEntity* getStartingQB() {
        //TODO create a list of constants for abbrevations
        return depth["QB"];
    }

private:
    std::map<std::string, PositionEntity*> depth = std::map<std::string, PositionEntity*>();
};

#endif //DEPTHCHART_H
