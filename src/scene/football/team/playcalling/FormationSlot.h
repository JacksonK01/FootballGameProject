//
// Created by jkirc on 8/18/2025.
//

#ifndef FORMATIONSLOT_H
#define FORMATIONSLOT_H

class PositionEntity;

struct FormationSlot {
    const PositionEntity& player;
    const double yardsFromLOS;
};

#endif //FORMATIONSLOT_H
