//
// Created by jkirc on 8/19/2025.
//

#ifndef ROUTE_H
#define ROUTE_H
#include <vector>

#include "../../../util/math/Vector2D.h"
#include "SFML/Graphics/RenderWindow.hpp"

//Basically just contains vectors.
//Routes are stored in yards, not pixels.
class Route {
public:
    ~Route() = default;

    Route() = default;

    explicit Route(const bool& isContinuous) : isContinuous(isContinuous) {}

    void addStep(const Vector2D& step) {
        path.emplace_back(step);
    }

    void render(double dt, sf::RenderWindow& window, const Vector2D& origin) const {
        Vector2D current = origin;

        for (auto& step : path) {
            Vector2D relativeStep = step + current;

            relativeStep.render(window, current);
            current = relativeStep;
        }
    }

    void incrementRouteStep() {
        step++;
    }

    Vector2D& getRouteStep() {
        if (isRouteDone()) {
            Logger::error("Route is finished!", typeid(*this));
        }
        return path[step];
    }

    bool isRouteDone() { return step >= path.size(); }

    void resetStep() { step = 0; }

protected:
    std::vector<Vector2D> path = std::vector<Vector2D>();
    int step = 0;
    bool isContinuous = false;
};

#endif //ROUTE_H
