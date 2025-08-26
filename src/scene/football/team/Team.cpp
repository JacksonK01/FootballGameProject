//
// Created by jkirc on 8/26/2025.
//

#include "Team.h"
#include "../../../event/EventBus.h"

Team::Team(EventBus &eventBus)
    : roster(eventBus.getEmitterInstance()),
      depthChart(roster)
{}

void Team::playcall() {

}



