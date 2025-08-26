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
    static Route go() {
        Route go = Route(true);
        go.addStep(Vector2D(50, 0));
        return go;
    }

    static Route dig() {
        Route dig = Route(false);
        dig.addStep(Vector2D(30, 0));
        dig.addStep(Vector2D(1, 2));
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

    static Route corner() {
        Route corner = Route(true);
        corner.addStep(Vector2D(10, 0));
        corner.addStep(Vector2D(10, -10));
        return corner;
    }

    static Route postCorner() {
        Route postCorner = Route(false);
        postCorner.addStep(Vector2D(20, 0));
        postCorner.addStep(Vector2D(1, 3));
        postCorner.addStep(Vector2D(10, -10));
        return postCorner;
    }

    static Route drag() {
        Route drag = Route(true);
        drag.addStep(Vector2D(2, 2));
        drag.addStep(Vector2D(0, 35));
        return drag;
    }
};

#endif //ROUTEPRESETS_H
