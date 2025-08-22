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

    Route(const std::vector<Vector2D>& path, const bool& isContinuous) : path(std::move(path)), isContinuous(isContinuous) {}

    //TODO impliment better.
    //O(n!)
    void render(double dt, sf::RenderWindow& window, const Vector2D& origin) const {
        std::vector<Vector2D> cache = std::vector<Vector2D>();
        for (auto& step : path) {
            auto scaled = step;

            for (auto& prev : cache) {
                scaled = scaled + prev;
            }

            (origin + scaled).render(window, origin);
            cache.emplace_back(step);
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
    std::vector<Vector2D> path;
    int step = 0;
    bool isContinuous = false;
};

#endif //ROUTE_H
