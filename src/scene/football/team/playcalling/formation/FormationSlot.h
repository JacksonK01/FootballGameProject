//
// Created by jkirc on 8/18/2025.
//

#pragma once

struct FormationSlot {
    const double x, y;
    const bool isEligible;

    FormationSlot(const double& x, const double& y, const bool& isEligible) : x(x), y(y), isEligible(isEligible) {}
};
