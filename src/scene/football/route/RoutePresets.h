//
// Created by jkirc on 8/23/2025.
//

#ifndef ROUTEPRESETS_H
#define ROUTEPRESETS_H
#include "Route.h"
#include "../field/FieldConstants.h"

//A route is in yards, not pixels
class RoutePresets {
public:
    static Route dig() {
        Route dig = Route(false);
        dig.addStep(Vector2D(50, 0));
        dig.addStep(Vector2D(0, 35));
        return dig;
    }

    static Route zig() {
        Route zig = Route(false);
        zig.addStep(Vector2D(7, 7));
        zig.addStep(Vector2D(0, -14));
        return zig;
    }

    static Route post() {
        Route post = Route(true);
        post.addStep(Vector2D(25, 0));
        post.addStep(Vector2D(25, 25));
        return post;
    }
};

#endif //ROUTEPRESETS_H
