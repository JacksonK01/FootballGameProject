//
// Created by jkirc on 8/10/2025.
//

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "Controller.h"
#include "../../../util/Logger.h"
#include "../../../util/math/Vector2D.h"
#include "../entity/positions/PositionEntity.h"

class PlayerController : public Controller {
public:
    explicit PlayerController(PositionEntity* linkedEntity) : linkedEntity(linkedEntity) {};

    void tick(double dt, PositionEntity &user, FootballField &field) override {

    };

    void onMouseClicked(const Vector2D pos) {
        if (linkedEntity) {
            linkedEntity->onMouseClicked(pos);
        } else {
            Logger::error("Missing Linked Entity", typeid(*this));
        }
    };

    void directionalInput(const Vector2D direction) {
        if (linkedEntity) {
            linkedEntity->onDirectionalInput(direction);
        } else {
            Logger::error("Missing Linked Entity", typeid(*this));
        }
    };

    void setLinkedEntity(PositionEntity* entity) {
        this->linkedEntity = entity;
    }

private:
    //Player will be linked to an entity to control
    PositionEntity* linkedEntity = nullptr;
};

#endif //PLAYERCONTROLLER_H
