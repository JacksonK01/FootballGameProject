//
// Created by jkirc on 8/18/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../field/FieldConstants.h"
#include "../field/FootballField.h"
#include "SFML/Graphics/View.hpp"

//This is basically a wrapper for view
class Camera {
public:
    explicit Camera(FootballField& field) : field(field) {}

    void render(double dt, sf::RenderWindow& window) {
        if (!toFollow) {
            return;
        }

        const float x = FieldConstants::toPixels(toFollow->getX());
        //const float y = FieldConstants::toPixels(toFollow->getY());

        const float fieldX = FieldConstants::toPixels(field.getPos().getX());
        const float fieldY = FieldConstants::toPixels(field.getPos().getY());

        view = sf::View(sf::FloatRect(sf::Vector2f(fieldX, fieldY), sf::Vector2f(FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX / 2, FieldConstants::FIELD_WIDTH_PX)));

        float halfWView = view.getSize().x / 2.f;
        //float halfHView = view.getSize().y / 2.f;

        float fieldW = FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX;
        //float fieldH = FieldConstants::FIELD_WIDTH_PX + FieldConstants::PIXEL_PER_YARD;

        float campX = std::clamp(x, halfWView, fieldW - halfWView);
        //float campY = std::clamp(y, halfHView, fieldH - halfHView);

        float centerY = (FieldConstants::FIELD_WIDTH_PX + FieldConstants::PIXEL_PER_YARD + fieldY) / 2;

        view.setCenter(sf::Vector2f(campX, centerY));
        window.setView(view);
    }

    void setFollowEntity(Entity* entity) {
        this->toFollow = entity;
    }

    bool doesHaveFocusEntity() const {
        return toFollow;
    }

private:
    sf::View view;
    Entity* toFollow = nullptr;
    FootballField& field;
};

#endif //CAMERA_H