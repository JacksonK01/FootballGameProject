//
// Created by jkirc on 8/10/2025.
//

#ifndef FOOTBALLFIELD_H
#define FOOTBALLFIELD_H
#include "FieldConstants.h"
#include "FieldState.h"
#include "../../../event/events/football/entity/FootballHitGroundEvent.h"
#include "../../../event/events/football/entity/ThrownPassEvent.h"
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

        if (!boundary.loadFromFile(prefix + "boundary_tile.png")) {
            Logger::error(errorMessage, typeid(*this));
        }

        registerEvents(eventBus);

        football.isVisible(false);
        getTeamOffense().getDepthChart().getStartingQB()->giveFootball(&football);

        int x = this->x + (FieldConstants::YARDS_FOR_FIRST * FieldConstants::PIXEL_PER_YARD / 2);
        int y = this->y + (FieldConstants::FIELD_WIDTH_YARDS * FieldConstants::PIXEL_PER_YARD / 2);
        team1.getDepthChart().getStartingQB()->setX(x);
        team1.getDepthChart().getStartingQB()->setY(y);

        team1.getDepthChart().getWR(0)->setX(x);
        team1.getDepthChart().getWR(0)->setY(y / 2);
    };

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
            auto footballHitGroundEvent = FootballHitGroundEvent(this->football);
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
            auto posVec = event.pos;

            Vector2D velocity = Vector2D(qb.getRatings().throwPower, qb.getRatings().throwPower);

            //I gotta make a way to streamline this, this is way too many methods.
            football.setX(qb.getX());
            football.setY(qb.getY());

            football.setVelocity(velocity);
            football.setDestination(posVec);
            football.isVisible(true);
            football.initiateThrow();

            qb.removeFootball();
        });

        //Test implementation
        eventBus.subscribe<FootballHitGroundEvent>([this](FootballHitGroundEvent& event) {
            auto qb = getTeamOffense().getDepthChart().getStartingQB();

            football.reset();
            football.isVisible(false);

            if (!qb->giveFootball(&football)) {
                Logger::error("Failed to give QB football", typeid(*this));
            }

        });

    }

    void renderGrassLayer(double dt, sf::RenderWindow& window) {
        double x = this->getPos().getX();
        double y = this->getPos().getY();

        //TODO move these out of the loop and scale the texture before game runs.
        sf::Sprite gSprite(grass);
        int spriteX = gSprite.getTextureRect().size.x;
        int spriteY = gSprite.getTextureRect().size.y;
        gSprite.setScale(sf::Vector2f(FieldConstants::PIXEL_PER_YARD / spriteX, FieldConstants::PIXEL_PER_YARD / spriteY));

        //Drass grass on every inch of the field there should be some
        for (int dx = x; dx < FieldConstants::ENTIRE_LENGTH_OF_FIELD; dx++) {
            for (int dy = y; dy < FieldConstants::FIELD_WIDTH_YARDS; dy++) {
                gSprite.setPosition(sf::Vector2f(dx * FieldConstants::PIXEL_PER_YARD, dy * FieldConstants::PIXEL_PER_YARD));
                window.draw(gSprite);
            }
        }
    }

    void renderBoundariesLayer(double dt, sf::RenderWindow& window) {
        double x = this->getPos().getX();
        double y = this->getPos().getY();

        //TODO move these out of the loop and scale the texture before game runs.
        sf::Sprite bSprite(boundary);
        int spriteX = bSprite.getTextureRect().size.x;
        int spriteY = bSprite.getTextureRect().size.y;
        bSprite.setScale(sf::Vector2f(FieldConstants::PIXEL_PER_YARD / spriteX, FieldConstants::PIXEL_PER_YARD / spriteY));

        for (int dx = x; dx < FieldConstants::ENTIRE_LENGTH_OF_FIELD + 1; dx++) {

            //TODO check if the dy should increment to FieldWidth + 2. It might be shrinking the field on accident here.
            for (int dy = y; dy < FieldConstants::FIELD_WIDTH_YARDS; dy++) {
                //This condition is for the top and bottom lines of the field, making sure they get rendered.
                if (dy == y || dy == FieldConstants::FIELD_WIDTH_YARDS - 1) {
                    bSprite.setPosition(sf::Vector2f(dx * FieldConstants::PIXEL_PER_YARD, dy * FieldConstants::PIXEL_PER_YARD));
                    window.draw(bSprite);
                } else if (dx % FieldConstants::YARDS_FOR_FIRST == 0) {
                    bSprite.setPosition(sf::Vector2f(dx * FieldConstants::PIXEL_PER_YARD, dy * FieldConstants::PIXEL_PER_YARD));
                    window.draw(bSprite);
                }
            }

        }
    }
};

#endif //FOOTBALLFIELD_H
