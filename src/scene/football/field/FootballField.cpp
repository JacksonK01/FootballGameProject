//
// Created by jkirc on 8/26/2025.
//

#include "FootballField.h"

#include "../entity/positions/PositionEntity.h"
#include "../../../event/EventBus.h"
#include "../../../event/events/football/entity/FootballHitGroundEvent.h"
#include "../../../event/events/football/entity/PassCaughtEvent.h"
#include "../../../event/events/football/entity/ThrownPassEvent.h"
#include "../route/RoutePresets.h"
#include "FieldConstants.h"
#include "../team/playcalling/formation/Formation.h"
#include "../team/playcalling/formation/presets/GunFormationPresets.h"
#include "SFML/Graphics/Sprite.hpp"

FootballField::FootballField(EventBus &eventBus) : eventBus(eventBus), team1(eventBus), team2(eventBus) {
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

    if (!dashes.loadFromFile(prefix + "field_dashes_tile.png")) {
        Logger::error(errorMessage, typeid(*this));
    }
    dashes.setRepeated(true);

    registerEvents(eventBus);

    football.isVisible(false);

    getTeamOffense().getDepthChart().getStartingQB()->giveFootball(&football);
    snapBall();
};

void FootballField::snapBall() {
    double x = this->x + FieldConstants::YARDS_FOR_FIRST * 2;
    double y = this->y + (FieldConstants::FIELD_WIDTH_YARDS / 2);

    Formation gun = GunFormationPresets::getGunBase();
    DepthChart& depth = getTeamOffense().getDepthChart();
    gun.alignPlayers(depth, *this, {x, y}, false);

    auto* wr1 = depth.getWR(0);
    auto* wr2 = depth.getWR(1);
    auto* wr3 = depth.getWR(2);

    auto r1 = RoutePresets::random();
    auto r2 = RoutePresets::random();
    auto r3 = RoutePresets::random();

    // Make sure r2 is not equal to r1
    while (r2 == r1) {
        r2 = RoutePresets::random();
    }

    // Make sure r3 is not equal to r1 or r2
    while (r3 == r1 || r3 == r2) {
        r3 = RoutePresets::random();
    }

    wr1->runRoute(r1);
    wr2->runRoute(r2);
    wr3->runRoute(r3);
}

void FootballField::tick(double dt) {
    switch (state) {
        case PLAY_CALLING: playCallingState(dt); break;
        case SNAP: snappedBallState(dt); break;
        default: {
            Logger::error("Missing Field State", typeid(*this));
        }
    }
}

void FootballField::render(double dt, sf::RenderWindow &window) {
    renderGrassLayer(dt, window);
    renderBoundariesLayer(dt, window);
    renderHashesLayer(dt, window);

    getTeamOffense().render(dt, window);
    football.render(dt, window);
}

PositionEntity *FootballField::collisionCheck(const util::Rectangle& hitbox) {

    for (auto* entity : getTeamOffense().getDepthChart().getOnFieldPlayers()) {
        if (entity->getBoundingBox().intersects(hitbox)) {
            return entity;
        }
    }

    return nullptr;
}

//Private methods

void FootballField::playCallingState(double dt) {
    team1.playcall();
    team2.playcall();
}

void FootballField::snappedBallState(double dt) {
    getTeamOffense().tick(dt);
    football.tick(dt);

    if (football.isOnGround()) {
        auto footballHitGroundEvent = FootballHitGroundEvent(football, football.getOwner());
        eventBus.emit(footballHitGroundEvent);
    }
}

void FootballField::registerEvents(EventBus &eventBus) {
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

        if (auto* collisionEntity = collisionCheck(box)) {
            auto catchEvent = PassCaughtEvent(collisionEntity, football);
            this->eventBus.emit(catchEvent);
        } else {
            event.thrower->giveFootball(&football);
        }
    });

    eventBus.subscribe<PassCaughtEvent>([this](PassCaughtEvent& event) {
        event.wr->giveFootball(&event.football);
    });
}

void FootballField::renderGrassLayer(double dt, sf::RenderWindow &window) {
    double scaledX = FieldConstants::toPixels(this->x);
    double scaledY = FieldConstants::toPixels(this->y);

    util::Rectangle entireField = {scaledX, scaledY, FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX, FieldConstants::FIELD_WIDTH_PX};

    sf::Sprite gSprite = entireField.getSpriteFromRectSize(grass);

    window.draw(gSprite);
}

void FootballField::renderBoundariesLayer(double dt, sf::RenderWindow &window) {
    double scaledX = FieldConstants::toPixels(this->x);
    double scaledY = FieldConstants::toPixels(this->y);

    util::Rectangle boundaryHorizontal = {scaledX, scaledY, FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX, FieldConstants::PIXEL_PER_YARD};

    sf::Sprite boundaryHSprite = boundaryHorizontal.getSpriteFromRectSize(boundary);
    window.draw(boundaryHSprite);
    boundaryHSprite.setPosition(sf::Vector2f(scaledX, FieldConstants::FIELD_WIDTH_PX + scaledY));
    window.draw(boundaryHSprite);

    util::Rectangle boundaryVertical = {scaledX, scaledY, FieldConstants::PIXEL_PER_YARD, FieldConstants::FIELD_WIDTH_PX};

    sf::Sprite boundaryVSprite = boundaryVertical.getSpriteFromRectSize(boundary);
    window.draw(boundaryVSprite);
    boundaryVSprite.setPosition(sf::Vector2f(scaledX + FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX - FieldConstants::PIXEL_PER_YARD, scaledY));
    window.draw(boundaryVSprite);

    double yardLineThickness = std::floor(std::max(FieldConstants::PIXEL_PER_YARD / 5, 1));

    util::Rectangle yardline = {scaledX, scaledY, yardLineThickness, FieldConstants::FIELD_WIDTH_PX};
    sf::Sprite vSprite = yardline.getSpriteFromRectSize(boundary);
    for (int dx = 1; dx < FieldConstants::ENTIRE_LENGTH_OF_FIELD / FieldConstants::YARDS_FOR_FIRST; dx++) {
        vSprite.setPosition(sf::Vector2f((dx * FieldConstants::PIXEL_PER_YARD * FieldConstants::YARDS_FOR_FIRST) + scaledX, scaledY));
        window.draw(vSprite);
    }
}

void FootballField::renderHashesLayer(double dt, sf::RenderWindow &window) const {
    const double scaledX = FieldConstants::toPixels(this->x);
    const double scaledY = FieldConstants::toPixels(this->y);

    const double yardLineThickness = std::floor(std::max(FieldConstants::PIXEL_PER_YARD, 1));

    const util::Rectangle hashLine = {scaledX, scaledY, FieldConstants::ENTIRE_LENGTH_OF_FIELD_PX, yardLineThickness};
    sf::Sprite hashLineSprite = hashLine.getSpriteFromRectSize(dashes);

    constexpr double yardsFromSideline = FieldConstants::YARDS_TO_HASHES_PX;

    hashLineSprite.setPosition(sf::Vector2f(scaledX, scaledY + yardsFromSideline));
    window.draw(hashLineSprite);

    const double dy = scaledY + (FieldConstants::FIELD_WIDTH_PX - yardsFromSideline);
    hashLineSprite.setPosition(sf::Vector2f(scaledX, dy));
    window.draw(hashLineSprite);
}










