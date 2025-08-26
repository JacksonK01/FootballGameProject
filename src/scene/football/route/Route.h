//
// Created by jkirc on 8/19/2025.
//

#pragma once

#include <vector>

#include "../../../util/math/Vector2D.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../field/FieldConstants.h"
#include "../../../src/util/Logger.h"

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

        int sizeTracker = 0;
        for (auto& step : path) {
            Vector2D relativeStep = step + current;

            sf::Color routeColor = sf::Color::Yellow;
            if (sizeTracker < path.size() - 1) {
                FieldConstants::toPixels(relativeStep).render(window, FieldConstants::toPixels(current), routeColor);
            } else {
                FieldConstants::toPixels(relativeStep).renderPointed(window, FieldConstants::toPixels(current), routeColor);
            }

            current = relativeStep;
            sizeTracker++;
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

