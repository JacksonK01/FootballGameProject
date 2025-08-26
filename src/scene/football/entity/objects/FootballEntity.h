//
// Created by jkirc on 8/10/2025.
//

#ifndef FOOTBALLENTITY_H
#define FOOTBALLENTITY_H
#include "../Entity.h"
#include "../../../../util/Logger.h"
#include "../../../../util/math/Vector2D.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class PositionEntity;

//Will be used to represent the actual football itself in game.
//A football's state will modify during a play and be reset once a play is over and the game moves to the next.
class FootballEntity : public Entity {
public:
    FootballEntity() : Entity({1.25, 1.35}) {
        if (!texture.loadFromFile("../assets/entity/Football.png")) {
            Logger::error("Football unable to load texture", typeid(*this));
        }
    }

    void tick(double dt) override {
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

    void render(double dt, sf::RenderWindow &window) override {
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

        if (Config::IS_DEBUG_MODE) {
            FieldConstants::toPixels(destination).render(window, scaledPos);
            scaledBoundingBox.render(window);
        }
    };

    void isVisible(const bool&& shouldRender) { this->shouldRender = shouldRender; }

    void setDestination(const Vector2D& dest) {
        this->destination = dest;
    }

    void initiateThrow() {
        this->isThrown = true;
    }

    void reset() {
        this->isThrown = false;
        this->shouldRender = false;
        this->isGrounded = false;
    }

    bool isOnGround() const { return this->isGrounded; }

    void setOwner(PositionEntity* owner) { this->owner = owner; }

    PositionEntity* getOwner() {
        if (!owner) {
            Logger::error("Football does not have owner", typeid(*this));
        }

        return owner;
    }

    bool doesHaveOwner() const {
        return owner;
    }

private:
    static constexpr int RANGE_IN_DEGREES = 60;

    double z = 0;

    //TODO fix magic numbers here
    //Starts at -1 for default value.
    //Cached once, gets the total throw distance
    double distanceCache = -1;
    //Tracks how far along the throw you are.
    double traveledDistance = 0;

    //Whoever threw ball
    PositionEntity* owner = nullptr;

    sf::Texture texture;
    Vector2D destination;

    //TODO Build a state machine for this.
    bool isThrown = false;
    bool shouldRender = false;
    bool isGrounded = false;
};

#endif //FOOTBALLENTITY_H
