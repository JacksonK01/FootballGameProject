//
// Created by jkirc on 8/26/2025.
//

#pragma once
#include "../Formation.h"
#include "../FormationSlot.h"

class GunFormationPresets {
public:
    static Formation getGunBase() {
        Formation gun = Formation(GUN);

        gun.addFormationSlot(QB, FormationSlot(HorizontalAlignment::ORIGIN, DepthAlignment::QB_GUN, {5, 0}, true));

        gun.addFormationSlot(WR, FormationSlot(HorizontalAlignment::LEFT_NUMBERS, DepthAlignment::LOS,true));
        // gun.addFormationSlot(WR, FormationSlot(HorizontalAlignment::RIGHT_NUMBERS, DepthAlignment::LOS, true));
        // gun.addFormationSlot(WR, FormationSlot(HorizontalAlignment::RIGHT_SLOT, DepthAlignment::SLOT, true));

        return gun;
    }
};
