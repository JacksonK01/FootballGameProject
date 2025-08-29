//
// Created by jkirc on 8/26/2025.
//
#include "../objects/FootballEntity.h"
#include "../../../src/event/Emitter.h"
#include "../../../../util/math/Vector2D.h"
#include "PositionEntity.h"

#include "../../../../config/Config.h"
#include "../../field/FieldConstants.h"
#include "../../../../event/events/football/entity/ThrownPassEvent.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RectangleShape.hpp"


PositionEntity::PositionEntity(Emitter &emitter, Position primaryPosition) : Entity(util::Rectangle(1.8, 2.9)), primaryPosition(primaryPosition), emitter(emitter) {
    std::string prefix = "../assets/texture/entity/position/";

    if (!dropbackTexture.loadFromFile(prefix + "qb.png")) {
        Logger::error("Unable to load QB texture", typeid(*this));
    }

    if (!idle.loadFromFile(prefix + "idle.png")) {
        Logger::error("Unable to load idle texture", typeid(*this));
    }

    //placeholder value for now.
    this->rating.speed = 12;
    this->rating.throwPower = 25;
}


void PositionEntity::onMouseClicked(const Vector2D &pos) {
    if (doesHaveFootball()) {
        ThrownPassEvent event = ThrownPassEvent(*this, getFootball(), pos);
        emitter.emit(event);
    } else {
        Logger::warn("Attempted to throw a pass without a football", typeid(*this));
    }

    const Vector2D lookVec = (pos - getPos()).normalize();
    setLookVec(lookVec);
};

void PositionEntity::onDirectionalInput(const Vector2D &direction) {
    looking = direction;
    this->velocity = Vector2D(direction.getX() * rating.speed, direction.getY() * rating.speed);
};

bool PositionEntity::removeFootball() {
    if (doesHaveFootball()) {
        football = nullptr;
        return true;
    }
    Logger::warn("This entity had no football to be removed", typeid(*this));
    return false;
}

bool PositionEntity::giveFootball(FootballEntity *football) {
    if (doesHaveFootball()) {
        return false;
    }

    this->football = football;
    return true;
}

void PositionEntity::runRoute(const Route &route) {
    this->state = RUN_ROUTE;

    //Creates a copy.
    this->route = std::move(route);

    routeOrigin = nullptr;
    routeStartPos = nullptr;
}

void PositionEntity::tick(double dt) {
    Entity::tick(dt);

    //TODO remove, only here for camera logic
    if (doesHaveFootball()) {
        getFootball().setX(x);
        getFootball().setY(y);
    }

    const double step = velocity.length() * dt;
    const Vector2D direction = velocity.normalize();

    this->x += step * direction.getX();
    this->y += step * direction.getY();

    if (velocity.length() > .1f) {
        velocity = velocity.multiply(0.75f);

        if (velocity.length() < .1f) {
            velocity = Vector2D();
        }
    }

    switch (state) {
        case IDLE: idleState(); break;
        case READY_TO_THROW: readyToThrow(); break;
        case RUN_ROUTE: runRoute(dt); break;
        default: {
            Logger::error("No State Active", typeid(*this));
        }
    }
}

void PositionEntity::render(double dt, sf::RenderWindow &window) {
    Vector2D pos = {x, y};

    Vector2D scaledPos = FieldConstants::toPixels(pos);
    util::Rectangle scaledBoundingBox = FieldConstants::toPixels(boundingBox);

    sf::Texture* toUse;

    if (doesHaveFootball()) {
        toUse = &dropbackTexture;
    } else {
        toUse = &idle;
    }

    sf::Sprite self = scaledBoundingBox.getSpriteFromRectangle(*toUse);

    if (route && state == RUN_ROUTE && !route->isRouteDone()) {
        if (!routeOrigin) {
            routeOrigin = new Vector2D(x, y);
        }

        route->render(dt, window, *routeOrigin);
    } else {
        routeOrigin = nullptr;
    }

    if (Config::RENDER_TEXTURES) {
        window.draw(self);
    } else {
        sf::RectangleShape dot = sf::RectangleShape(sf::Vector2f(6, 6));
        dot.setFillColor(sf::Color::Red);
        dot.setPosition(sf::Vector2f(FieldConstants::toPixels(this->x), FieldConstants::toPixels(this->y)));
        window.draw(dot);
    }

    if (Config::IS_DEBUG_MODE) {
        FieldConstants::toPixels(velocity + pos).renderPointed(window, scaledPos, sf::Color::Blue);
        FieldConstants::toPixels(looking + pos).renderPointed(window, scaledPos, sf::Color::Magenta);

        scaledBoundingBox.render(window);
    }
}

FootballEntity &PositionEntity::getFootball() {
    //Checks if football is not null
    if (!doesHaveFootball()) {
        //This will throw an error if it does not have it.
        Logger::error("Entity tried accessing football when it did not have it.", typeid(*this));
    }
    return *football;
}

void PositionEntity::idleState() {

}

void PositionEntity::readyToThrow() {

}

void PositionEntity::runRoute(double dt) {
    if (!route || route->isRouteDone() || doesHaveFootball()) {
        this->state = IDLE;
        return;
    }

    if (!routeStartPos) {
        routeStartPos = new Vector2D(x, y);
    }

    const Vector2D currentPos = {x, y};

    const Vector2D destination = (route->getRouteStep() + *routeStartPos) - currentPos;

    const Vector2D direction = destination.normalize();

    setLookVec(direction);

    setVelocity({rating.speed * direction.getX(), rating.speed * direction.getY()});

    double range = velocity.length() * dt;
    if (destination.length() <= range) {
        routeStartPos = nullptr;
        route->incrementRouteStep();
    }
}






