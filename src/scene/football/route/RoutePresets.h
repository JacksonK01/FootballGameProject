//
// Created by jkirc on 8/23/2025.
//

#ifndef ROUTEPRESETS_H
#define ROUTEPRESETS_H
#include "Route.h"
#include "../field/FieldConstants.h"

class RoutePresets {
public:
    static Route dig() {
        Route dig = Route(false);
        dig.addStep(Vector2D(50 * FieldConstants::PIXEL_PER_YARD, 0));
        dig.addStep(Vector2D(0, 35 * FieldConstants::PIXEL_PER_YARD));
        return dig;
    }

};

#endif //ROUTEPRESETS_H
