//
// Created by jkirc on 8/10/2025.
//

#ifndef FOOTBALLFIELD_H
#define FOOTBALLFIELD_H
#include "FieldConstants.h"
#include "FieldState.h"
#include "../../../event/events/football/entity/FootballHitGroundEvent.h"
#include "../../../event/events/football/entity/PassCaughtEvent.h"
#include "../../../event/events/football/entity/ThrownPassEvent.h"
#include "../route/RoutePresets.h"
#include "../team/Team.h"
#include "SFML/Graphics/RenderWindow.hpp"

//Class for storing who's on the field, who is where, houses each player in one place.
//Possibly should house interaction logic between players? Will decide later.
class FootballField {
public:
    explicit FootballField(EventBus& eventBus): eventBus(eventBus), team1(eventBus), team2(eventBus) {
        std::string errorMessage = "Unable to load tile texture for field";
        std::string prefix = "../assets/texture/tile/";

        if (!grass.loadFromFile(prefix + "grass_tile.png")) {
            Logger::error(errorMessage, typeid(*this));
        }
        grass.setRepeated(true);

        if (!boundary.loadFromFile(prefix + "boundary_tile.png")) {
            Logger::error(errorMessage, typeid(*this));
        }
        boundary.setRepeated(true);

        registerEvents(eventBus);

        football.isVisible(false);
        getTeamOffense().getDepthChart().getStartingQB()->giveFootball(&football);

        snapBall();
    };

    //Called when space bar input
    //For now will just be a pos reset
    void snapBall() {
        double x = this->x + (FieldConstants::YARDS_FOR_FIRST / 2);
        double y = this->y + (FieldConstants::FIELD_WIDTH_YARDS / 2);

        auto* qb = getTeamOffense().getDepthChart().getStartingQB();
        qb->setX(x);
        qb->setY(y);

        auto* wr = getTeamOffense().getDepthChart().getWR(0);
        wr->setX(x);
        wr->setY(y / 2);

        int totalRoutesAddedToGame = 8;
        // Random route selection
        int routeIndex = std::rand() % totalRoutesAddedToGame;
        Route selectedRoute;

        switch (routeIndex) {
            case 0: selectedRoute = RoutePresets::dig(); break;
            case 1: selectedRoute = RoutePresets::zig(); break;
            case 2: selectedRoute = RoutePresets::post(); break;
            case 3: selectedRoute = RoutePresets::corner(); break;
            case 4: selectedRoute = RoutePresets::postCorner(); break;
            case 5: selectedRoute = RoutePresets::drag(); break;
            case 6: selectedRoute = RoutePresets::sluggo(); break;
            default: selectedRoute = RoutePresets::go(); break;
        }

        wr->runRoute(selectedRoute);
    }

    void tick(double dt) {
        switch (state) {
            case PLAY_CALLING: playCallingState(dt); break;
            case SNAP: snappedBallState(dt); break;
            default: {
                Logger::error("Missing Field State", typeid(*this));
            }
        }
    };

    void render(double dt, sf::RenderWindow& window) {
        renderGrassLayer(dt, window);
        renderBoundariesLayer(dt, window);

        team1.getDepthChart().getStartingQB()->render(dt, window);
        team1.getDepthChart().getWR(0)->render(dt, window);
        football.render(dt, window);
    };

    //TODO this will need to be replaced with getTeamOffense and getTeamDefense.
    Team& getTeamOffense() { return team1; }

    Vector2D getPos() const { return {this->x, this->y}; }

private:
    EventBus& eventBus;
    Team team1;
    Team team2;
    FootballEntity football;
    FieldState state = FieldState::SNAP;

    sf::Texture texture;

    double x = 0;
    double y = 0;

    sf::Texture grass;
    sf::Texture boundary;

    void playCallingState(double dt) {
        team1.playcall();
        team2.playcall();
    }

    //For when the ball gets snapped
    void snappedBallState(double dt) {
        team1.getDepthChart().getStartingQB()->tick(dt);
        team1.getDepthChart().getWR(0)->tick(dt);
        football.tick(dt);

        if (football.isOnGround()) {
            auto footballHitGroundEvent = FootballHitGroundEvent(football, football.getOwner());
            eventBus.emit(footballHitGroundEvent);
        }
    }

    //Using this in a lambda capture gives a POINTER of the object. Feels like pointers have no standard in C++, imo should be able to do
    //something like *this to de-reference and pass a reference into the lambda. If you want to capture all variables used in a lambda
    //you can do [&]() {};
    //Lambdas just have their own rules for captures :|
    void registerEvents(EventBus& eventBus) {

        eventBus.subscribe<ThrownPassEvent>([this](ThrownPassEvent& event) {
            auto& qb = event.qb;
            auto dest = event.pos;

            Vector2D velocity = Vector2D(qb.getRatings().throwPower, qb.getRatings().throwPower);

            //I gotta make a way to streamline this, this is way too many methods.
            football.setX(qb.getX());
            football.setY(qb.getY());

            football.setVelocity(velocity + qb.getVelocity().getAbs());
            football.setDestination(dest);
            football.isVisible(true);
            football.setLookVec((dest - Vector2D(qb.getX(), qb.getY())).normalize());
            football.initiateThrow();

            football.setOwner(&qb);

            qb.removeFootball();
        });

        //Test implementation
        eventBus.subscribe<FootballHitGroundEvent>([this](FootballHitGroundEvent& event) {
            football.reset();
            football.isVisible(false);

            const util::Rectangle& box = football.getBoundingBox().inflate(1);

            auto* wr = getTeamOffense().getDepthChart().getWR(0);
            auto* qb = getTeamOffense().getDepthChart().getStartingQB();

            if (wr->getBoundingBox().intersects(box)) {
                auto catchEvent = PassCaughtEvent(wr, football);
                this->eventBus.emit(catchEvent);
            } else if (qb->getBoundingBox().intersects(box)) {
                auto catchEvent = PassCaughtEvent(qb, football);
                this->eventBus.emit(catchEvent);
            } else {
                event.thrower->giveFootball(&football);
            }
        });

        eventBus.subscribe<PassCaughtEvent>([this](PassCaughtEvent& event) {
            event.wr->giveFootball(&event.football);
        });

    }

    void renderGrassLayer(double dt, sf::RenderWindow& window) {
        util::Rectangle entireField = {this->x, this->y, FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX, FieldConstants::FIELD_WIDTH_PX};

        sf::Sprite gSprite = entireField.getSpriteFromRectSize(grass);

        window.draw(gSprite);
    }

    void renderBoundariesLayer(double dt, sf::RenderWindow& window) {
        util::Rectangle boundaryHorizontal = {this->x, this->y, FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX, FieldConstants::PIXEL_PER_YARD};

        sf::Sprite boundaryHSprite = boundaryHorizontal.getSpriteFromRectSize(boundary);
        window.draw(boundaryHSprite);
        boundaryHSprite.setPosition(sf::Vector2f(this->x, FieldConstants::FIELD_WIDTH_PX));
        window.draw(boundaryHSprite);

        util::Rectangle boundaryVertical = {this->x, this->y, FieldConstants::PIXEL_PER_YARD, FieldConstants::FIELD_WIDTH_PX};

        sf::Sprite boundaryVSprite = boundaryVertical.getSpriteFromRectSize(boundary);
        window.draw(boundaryVSprite);
        boundaryVSprite.setPosition(sf::Vector2f(FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX - FieldConstants::PIXEL_PER_YARD, this->y));
        window.draw(boundaryVSprite);

        double yardLineThickness = std::max(FieldConstants::PIXEL_PER_YARD / 5, 1);

        util::Rectangle yardline = {this->x, this->y, yardLineThickness, FieldConstants::FIELD_WIDTH_PX};
        sf::Sprite vSprite = yardline.getSpriteFromRectSize(boundary);
        for (int dx = this->x + 1; dx < FieldConstants::ENTIRE_LENGTH_OF_FIELD / FieldConstants::YARDS_FOR_FIRST; dx++) {
            vSprite.setPosition(sf::Vector2f(dx * FieldConstants::PIXEL_PER_YARD * FieldConstants::YARDS_FOR_FIRST, this->y));
            window.draw(vSprite);
        }
    }
};

#endif //FOOTBALLFIELD_H
