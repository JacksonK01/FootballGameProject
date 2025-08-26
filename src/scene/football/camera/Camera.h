//
// Created by jkirc on 8/18/2025.
//

#pragma once

#include "SFML/Graphics/View.hpp"

class FootballField;
class Entity;

namespace sf {
    class RenderWindow;
}

//This is basically a wrapper for view
class Camera {
public:
    explicit Camera(FootballField& field);

    void render(double dt, sf::RenderWindow& window);

    void setFollowEntity(Entity* entity) { this->toFollow = entity; }

    bool doesHaveFocusEntity() const { return toFollow; }

private:
    sf::View view;
    Entity* toFollow = nullptr;
    FootballField& field;
};