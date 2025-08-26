//
// Created by jkirc on 8/10/2025.
//

#pragma once

#include "../../../src/util/math/Vector2D.h"
#include "../../../src/util/Rectangle.h"

namespace sf {
    class RenderWindow;
}

// Bases for every entity, like QBs and RBs and the football itself.
class Entity {
public:
    virtual ~Entity() = default;

    Entity() : boundingBox(x, y, 0, 0) {}

    Entity(double x, double y, const util::Rectangle& boundingBox) : x(x), y(y), boundingBox(boundingBox) {}

    explicit Entity(const util::Rectangle& boundingBox) : boundingBox(boundingBox) {};

    virtual void tick(double dt) {
        boundingBox.centerToPos({x, y});
    }

    virtual void render(double dt, sf::RenderWindow& window) = 0;

    // Getters
    [[nodiscard]] double getX() const { return x; }
    [[nodiscard]] double getY() const { return y; }
    [[nodiscard]] util::Rectangle getBoundingBox() const { return boundingBox; }
    [[nodiscard]] Vector2D getVelocity() const { return velocity; };
    [[nodiscard]] Vector2D getLookVector() const { return looking; };

    // Setters
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setBoundingBox(const util::Rectangle& newBoundingBox) { boundingBox = newBoundingBox; }
    void setVelocity(const Vector2D& velocity) { this->velocity = velocity; }
    void setLookVec(const Vector2D& direction) { this->looking = direction; }

protected:
    //The x and y are stored in yards not pixels
    double x = 0, y = 0;
    util::Rectangle boundingBox;
    Vector2D velocity;
    //Should always be normalized
    Vector2D looking;
};

