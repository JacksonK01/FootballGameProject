//
// Created by jkirc on 8/26/2025.
//

#pragma once
#include "../Formation.h"

class GunFormationPresets {
public:
    static Formation getGunBase() {
        Formation gun = Formation(GUN);

        gun.addFormationSlot(QB, FormationSlot(4, 0, false));

        gun.addFormationSlot(WR, FormationSlot(0, 12, true));
        gun.addFormationSlot(WR, FormationSlot(1, -7, true));
        gun.addFormationSlot(WR, FormationSlot(0, -14, true));

        return gun;
    }
};
