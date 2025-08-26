//
// Created by jkirc on 8/26/2025.
//

#include "FootballScene.h"

#include "../../event/events/football/entity/PassCaughtEvent.h"
#include "../../event/events/football/entity/ThrownPassEvent.h"


void FootballScene::registerEvents() {
    eventBus.subscribe<PassCaughtEvent>([this](PassCaughtEvent& event) {
        player1.setLinkedEntity(event.wr);
    });

    eventBus.subscribe<ThrownPassEvent>([this](ThrownPassEvent& event) {
        camera.setFollowEntity(&event.football);
    });

    eventBus.subscribe<PassCaughtEvent>([this](PassCaughtEvent& event) {
        camera.setFollowEntity(event.wr);
    });
}
