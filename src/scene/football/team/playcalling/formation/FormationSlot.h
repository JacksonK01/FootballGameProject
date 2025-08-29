//
// Created by jkirc on 8/18/2025.
//

#pragma once
#include "../../../../../util/math/Vector2D.h"

enum class HorizontalAlignment {
    LEFT_SIDELINE,
    RIGHT_SIDELINE,
    LEFT_NUMBERS,
    RIGHT_NUMBERS,
    LEFT_SLOT,
    RIGHT_SLOT,
    INLINE,
    ORIGIN,
    CUSTOM
};

enum class DepthAlignment {
    BACKFIELD,
    LOS,
    SLOT,
    QB_GUN,
    CUSTOM
};

struct FormationSlot {
    HorizontalAlignment horizontal;
    DepthAlignment depth;

    Vector2D offset;
    const bool isEligible;

    FormationSlot(const HorizontalAlignment& horizontal, const DepthAlignment& depth,
        const Vector2D& offset, const bool& isEligible) : horizontal(horizontal), depth(depth), offset(offset), isEligible(isEligible) {}

    FormationSlot(const HorizontalAlignment& horizontal, const DepthAlignment& depth,
        const bool& isEligible) : FormationSlot(horizontal, depth, {0, 0}, isEligible) {}
};
