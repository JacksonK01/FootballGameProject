//
// Created by jkirc on 8/10/2025.
//

#ifndef POSITIONENTITY_H
#define POSITIONENTITY_H
#include "PositionEntityState.h"
#include "../Entity.h"
#include "../../../../event/events/football/entity/ThrownPassEvent.h"
#include "../../route/Route.h"

#include "../../util/Position.h"
#include "../objects/FootballEntity.h"
#include "rating/Ratings.h"

//This will be the base class to represent a position as an entity. These entities will be built to be controlled by a player or an AI. Will be the
//base class for positions within football I.E. QB, RB, WR, CB.
//Will have base attributes like Stamina, Strength, Awareness, and ETC
//Any position will be able to do anything.
class PositionEntity : public Entity {
public:
    //TODO delete this, just place holder
    static constexpr float SCALE = 3.f;

    explicit PositionEntity(Emitter& emitter, Position primaryPosition) : primaryPosition(primaryPosition), emitter(emitter) {
        std::string prefix = "../assets/texture/entity/position/";

        if (!dropbackTexture.loadFromFile(prefix + "qb.png")) {
            Logger::error("Unable to load QB texture", typeid(*this));
        }

        if (!idle.loadFromFile(prefix + "idle.png")) {
            Logger::error("Unable to load idle texture", typeid(*this));
        }

        boundingBox.setWidth(16 * SCALE);
        boundingBox.setHeight(16 * SCALE);

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
    bool doesHaveFootball() {
        return this->football;
    }

    Rating getRatings() { return rating; }

    Position getPosition() { return primaryPosition; }

    void tick(double dt) override {
        Entity::tick(dt);

        switch (state) {
            case IDLE: idleState();
            case READY_TO_THROW: readyToThrow();
        }
    }

    void render(double dt, sf::RenderWindow &window) override {
        sf::Texture* toUse;
        if (doesHaveFootball()) {
            toUse = &dropbackTexture;
        } else {
            toUse = &idle;
        }

        sf::Sprite self(*toUse);
        self.setPosition(sf::Vector2f(x, y));
        self.scale(sf::Vector2f(SCALE, SCALE));

        if (route) {
            route->render(dt, window);
        }

        window.draw(self);
        if (Config::IS_DEBUG_MODE) {
            boundingBox.render(window);
        }
    }

protected:
    //Although a position entity can play and do whatever needed, they still need to know what they are.
    Position primaryPosition;
    Rating rating;
    Emitter& emitter;
    Route* route = nullptr;
    PositionEntityState state = IDLE;

    //Generic texture
    sf::Texture idle;
    //Qb texture
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

    void idleState() {}

    void readyToThrow() {}
};

#endif //POSITIONENTITY_H
