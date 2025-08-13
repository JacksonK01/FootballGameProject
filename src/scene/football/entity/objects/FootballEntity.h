//
// Created by jkirc on 8/10/2025.
//

#ifndef FOOTBALLENTITY_H
#define FOOTBALLENTITY_H
#include "../Entity.h"
#include "../../../../util/Logger.h"
#include "../../../../util/math/Vector2D.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Texture.hpp"

//Will be used to represent the actual football itself in game.
//A football's state will modify during a play and be reset once a play is over and the game moves to the next.
class FootballEntity : public Entity {
public:
    FootballEntity() : Entity() {
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

            double range = 10;
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

                int speedScale = 10.0;
                int step = velocity.length() * speedScale * dt;

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

        float size = 75.f;
        sf::RectangleShape ball = sf::RectangleShape(sf::Vector2f(size, size));
        ball.setOrigin(sf::Vector2f(0.f, size / 2));
        ball.setPosition(sf::Vector2f(x, y - z));
        ball.setTexture(&texture);

        window.draw(ball);
    };

    void isVisible(const bool&& shouldRender) { this->shouldRender = shouldRender; }

    void setDestination(const Vector2D& dest) {
        this->destination = dest;
    }

    void setVelocity(const Vector2D& vel) {
        this->velocity = std::move(vel);
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

private:
    double z = 0;

    //Starts at -1 for default value.
    //Cached once, gets the total throw distance
    double distanceCache = -1;
    //Tracks how far along the throw you are.
    double traveledDistance = 0;



    sf::Texture texture;
    Vector2D destination;
    Vector2D velocity;

    //TODO Build a state machine for this.
    bool isThrown = false;
    bool shouldRender = false;
    bool isGrounded = false;
};

#endif //FOOTBALLENTITY_H
