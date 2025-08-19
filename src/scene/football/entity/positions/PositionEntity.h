//
// Created by jkirc on 8/10/2025.
//

#ifndef POSITIONENTITY_H
#define POSITIONENTITY_H
#include "../Entity.h"
#include "../../../../event/events/football/entity/ThrownPassEvent.h"
#include "../../util/Position.h"
#include "../objects/FootballEntity.h"
#include "rating/Ratings.h"

//This will be the base class to represent a position as an entity. These entities will be built to be controlled by a player or an AI. Will be the
//base class for positions within football I.E. QB, RB, WR, CB.
//Will have base attributes like Stamina, Strength, Awareness, and ETC
//Any position will be able to do anything.
class PositionEntity : public Entity {
public:
    explicit PositionEntity(Emitter& emitter, Position primaryPosition) : primaryPosition(primaryPosition), emitter(emitter) {
        //Checks if texture does not load
        if (!dropbackTexture.loadFromFile("../assets/entity/QB.png")) {
            Logger::error("QB unable to load texture", typeid(*this));
        }

        //placeholder value for now.
        this->rating.speed = 5;
        this->rating.throwPower = 50;
    }

    //For inputs from a player controller
    void onMouseClicked(const Vector2D& pos) {
        if (doesHaveFootball()) {
            ThrownPassEvent event = ThrownPassEvent(*this, pos);
            emitter.emit(event);
        } else {
            Logger::warn("Attempted to throw a pass without a football", typeid(*this));
        }
    };

    void onDirectionalInput(const Vector2D& direction) {
        this->x += direction.getX() * this->rating.speed;
        this->y += direction.getY() * this->rating.speed;
    };

    //Returns true if football is successfully removed
    virtual bool removeFootball() {
        if (doesHaveFootball()) {
            football = nullptr;
            return true;
        }
        Logger::warn("This entity had no football to be removed", typeid(*this));
        return false;
    }

    //returns true if football can be given.
    virtual bool giveFootball(FootballEntity* football) {
        if (doesHaveFootball()) {
            return false;
        }

        this->football = football;
        return true;
    }

    //returns true if have football
    virtual bool doesHaveFootball() {
        return this->football;
    }

    Rating getRatings() { return rating; }

    Position getPosition() { return primaryPosition; }

    void render(double dt, sf::RenderWindow &window) override {
        sf::Sprite qb(dropbackTexture);
        qb.setPosition(sf::Vector2f(x, y));
        qb.scale(sf::Vector2f(3.f, 3.f));

        window.draw(qb);
    }

protected:
    //Although a position entity can play and do whatever needed, they still need to know what they are.
    Position primaryPosition;
    Rating rating;
    Emitter& emitter;

    sf::Texture dropbackTexture;

    //Meant for only internals
    FootballEntity& getFootball() {
        //Checks if football is not null
        if (!doesHaveFootball()) {
            //This will throw an error if it does not have it.
            Logger::error("Entity tried accessing football when it did not have it.", typeid(*this));
        }
        return *football;
    }

private:
    FootballEntity* football = nullptr;
};

#endif //POSITIONENTITY_H
