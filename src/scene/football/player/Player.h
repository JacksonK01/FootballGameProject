//
// Created by jkirc on 8/10/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../entity/Entity.h"

//Is not a direct entity, rather it controls a linked entity, that way a player can switch what position it wants to play as.
class Player {
public:
    Player();
private:
    Entity* linkedEntity;
};

#endif //PLAYER_H
