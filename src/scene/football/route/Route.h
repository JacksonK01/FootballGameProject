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

    explicit Route(const Vector2D& origin) : origin(std::move(origin)), path() {}
    Route(const Vector2D& origin, const std::vector<Vector2D>& path) : origin(std::move(origin)), path(std::move(path)) {}

    void render(double dt, sf::RenderWindow& window) const {
        for (auto& part : path) {
            part.render(window, origin);
        }
    }

protected:
    Vector2D origin;
    std::vector<Vector2D> path;
};

#endif //ROUTE_H
