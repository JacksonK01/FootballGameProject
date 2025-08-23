//
// Created by jkirc on 8/10/2025.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "../../../util/Rectangle.h"
#include "SFML/Graphics/RenderWindow.hpp"

// Bases for every entity, like QBs and RBs and the football itself.
class Entity {
public:
    virtual ~Entity() = default;

    Entity() : x(0), y(0), boundingBox(x, y, 0, 0) {}

    Entity(double x, double y, const util::Rectangle& boundingBox) : x(x), y(y), boundingBox(boundingBox) {}

    virtual void tick(double dt) {
        boundingBox.setX(this->x);
        boundingBox.setY(this->y);
    }

    virtual void render(double dt, sf::RenderWindow& window) = 0;

    // Getters
    [[nodiscard]] double getX() const { return x; }
    [[nodiscard]] double getY() const { return y; }
    [[nodiscard]] util::Rectangle getBoundingBox() const { return boundingBox; }

    // Setters
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setBoundingBox(const util::Rectangle& newBoundingBox) { boundingBox = newBoundingBox; }

protected:
    //The x and y are stored in yards not pixels
    double x, y;
    util::Rectangle boundingBox;
};

#endif // ENTITY_H
