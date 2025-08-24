//
// Created by jkirc on 8/10/2025.
//

#ifndef POSITIONENTITY_H
#define POSITIONENTITY_H
#include "PositionEntityState.h"
#include "../Entity.h"
#include "../../../../event/events/football/entity/ThrownPassEvent.h"
#include "../../field/FieldConstants.h"
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
        this->rating.speed = 150;
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
        looking = direction;
        this->velocity = Vector2D(direction.getX() * rating.speed, direction.getY() * rating.speed);
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

    void setState(const PositionEntityState& state) { this->state = state; }

    void runRoute(const Route& route) {
        this->state = RUN_ROUTE;

        //Creates a copy.
        this->route = std::move(route);
    }

    void tick(double dt) override {
        Entity::tick(dt);

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

        if (route && state == RUN_ROUTE && !route->isRouteDone()) {
            if (!routeOrigin) {
                routeOrigin = new Vector2D(x, y);
            }

            route->render(dt, window, *routeOrigin);
        } else {
            routeOrigin = nullptr;
        }

        window.draw(self);
        if (Config::IS_DEBUG_MODE) {
            Vector2D pos = {x, y};
            (velocity + pos).render(window, pos, sf::Color::Blue);
            (looking + pos).render(window, pos, sf::Color::Magenta);
            boundingBox.render(window);
        }
    }

protected:
    //Although a position entity can play and do whatever needed, they still need to know what they are.
    Position primaryPosition;
    Rating rating;
    Emitter& emitter;
    std::optional<Route> route;
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
    //TODO delete routeStartPos, it's a dummy value for run route to know where the entity started
    Vector2D* routeStartPos = nullptr;

    //TODO delete routeOrigin, used to know where to keep rendering the route
    Vector2D* routeOrigin = nullptr;

    void idleState() {}

    void readyToThrow() {}

    void runRoute(double dt) {
        if (!route || route->isRouteDone() || doesHaveFootball()) {
            this->state = IDLE;
            return;
        }

        if (!routeStartPos) {
            routeStartPos = new Vector2D(x, y);
        }

        Vector2D currentPos = {x, y};

        Vector2D destination = (route->getRouteStep() + *routeStartPos) - currentPos;

        Vector2D direction = destination.normalize();

        looking = direction.multiply(FieldConstants::PIXEL_PER_YARD);

        setVelocity({rating.speed * direction.getX(), rating.speed * direction.getY()});

        double range = 15;
        if (destination.length() <= range) {
            routeStartPos = nullptr;
            route->incrementRouteStep();
        }
    }
};

#endif //POSITIONENTITY_H
