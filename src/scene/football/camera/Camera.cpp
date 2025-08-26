//
// Created by jkirc on 8/26/2025.
//

#include "Camera.h"
#include "../field/FootballField.h"
#include "../field/FieldConstants.h"

Camera::Camera(FootballField &field) : field(field) {}

void Camera::render(double dt, sf::RenderWindow &window) {
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

    float campX = std::clamp(x, halfWView, fieldW - halfWView) + fieldX;
    //float campY = std::clamp(y, halfHView, fieldH - halfHView);

    float centerY = (FieldConstants::FIELD_WIDTH_PX + FieldConstants::PIXEL_PER_YARD) / 2;
    centerY += fieldY;

    view.setCenter(sf::Vector2f(campX, centerY));
    window.setView(view);
}

