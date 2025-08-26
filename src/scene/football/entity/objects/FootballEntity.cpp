//
// Created by jkirc on 8/26/2025.
//
#include "FootballEntity.h"

#include "../../../src/config/Config.h"
#include "../../field/FieldConstants.h"
#include "../../../../util/Logger.h"
#include "../../../../util/math/Vector2D.h"
#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

FootballEntity::FootballEntity(): Entity({1.25, 1.35}) {
    if (!texture.loadFromFile("../assets/entity/Football.png")) {
        Logger::error("Football unable to load texture", typeid(*this));
    }
}

void FootballEntity::tick(double dt) {
    Entity::tick(dt);

    if (isThrown) {
        Vector2D currentPos = Vector2D(x, y);
        Vector2D directDestination = (destination - currentPos);

        if (distanceCache == -1) {
            distanceCache = directDestination.length();
        }

        double range = velocity.length() * dt;
        if (directDestination.length() <= range) {
            //TODO gotta add a state machine to avoid code like this.
            isGrounded = true;
            isThrown = false;
            x = destination.getX();
            y = destination.getY();
            z = 0;

            distanceCache = -1;
            traveledDistance = 0;
        } else {
            Vector2D direction = directDestination.normalize();

            double step = velocity.length() * dt;

            x += direction.getX() * step;
            y += direction.getY() * step;

            traveledDistance += step;

            //range 0-1
            double progress = traveledDistance / distanceCache;
            if (progress > 1) progress = 1;

            double zScale = distanceCache * 0.5;
            z = zScale * progress * (1 - progress);
        }
    }
}

void FootballEntity::render(double dt, sf::RenderWindow &window) {
    if (!shouldRender) {
        return;
    }

    Vector2D pos = {x, y};
    Vector2D scaledPos = FieldConstants::toPixels(pos);
    util::Rectangle scaledBoundingBox = FieldConstants::toPixels(boundingBox);

    sf::Sprite ball = scaledBoundingBox.getSpriteFromRectangle(texture);
    ball.setPosition(sf::Vector2f(FieldConstants::toPixels(x), FieldConstants::toPixels(y - z)));

    double degrees = std::atan2(looking.getY(), looking.getX()) * 180 / M_PI;

    if (looking.getX() < 0) {
        degrees += 180.0;
    }

    //Will angle the football if it's outside a 120 degree cone
    if (-RANGE_IN_DEGREES > degrees || degrees > RANGE_IN_DEGREES) {
        sf::Angle stepAngle = sf::degrees(degrees);
        ball.setRotation(stepAngle);
    }

    window.draw(ball);

    //This was debug before but proved to be useful
    //TODO possibly remove in the future
    FieldConstants::toPixels(destination).render(window, scaledPos);

    if (Config::IS_DEBUG_MODE) {
        scaledBoundingBox.render(window);
    }
}

void FootballEntity::reset() {
    this->isThrown = false;
    this->shouldRender = false;
    this->isGrounded = false;
}

PositionEntity *FootballEntity::getOwner() {
    if (!owner) {
        Logger::error("Football does not have owner", typeid(*this));
    }

    return owner;
}




