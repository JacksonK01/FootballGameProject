//
// Created by jkirc on 8/10/2025.
//

#ifndef FOOTBALLFIELD_H
#define FOOTBALLFIELD_H
#include "Yard.h"
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
        //Checks if texture does not load
        //Dev art :((
        //This field is put in place to put a loose idea on how the game's camera will look.
        // if (!texture.loadFromFile("../assets/field/Field.png")) {
        //     Logger::error("Field unable to load texture", typeid(*this));
        // }

        football.isVisible(false);
        getTeamOffense().getDepthChart().getStartingQB()->giveFootball(&football);



    };

    void tick(double dt) {
        team1.getDepthChart().getStartingQB()->tick(dt);
        football.tick(dt);

        if (football.isOnGround()) {
            auto footballHitGroundEvent = FootballHitGroundEvent(this->football);
            eventBus.emit(footballHitGroundEvent);
        }
    };

    void render(double dt, sf::RenderWindow& window) {
        // sf::RectangleShape field = sf::RectangleShape(sf::Vector2f(window.getSize()));
        // field.setTexture(&texture);
        // window.draw(field);
        renderField(dt, window);

        team1.getDepthChart().getStartingQB()->render(dt, window);
        football.render(dt, window);
    };

    //TODO this will need to be replaced with getTeamOffense and getTeamDefense.
    Team& getTeamOffense() { return team1; }

private:
    EventBus& eventBus;
    Team team1;
    Team team2;
    FootballEntity football;

    sf::Texture texture;


    //These next few variables are for doing the nitty gritty of calculating the field.
    int x = 0;
    int y = 0;

    //100 Yards long
    Yard horizontalDistance = Yard(this->x, this->y, 100);
    Yard verticalDistance = Yard(this->x, this->y, 53);
    sf::Texture grass;
    sf::Texture boundary;

    void renderField(double dt, sf::RenderWindow& window) {
        for (int x = this->x; x < horizontalDistance.getAmountOfYards(); x++) {
            for (int y = this->y; y < verticalDistance.getAmountOfYards(); y++) {
                sf::Sprite gSprite(grass);

                int scale = Yard::PIXEL_PER_YARD;

                gSprite.scale(sf::Vector2f(2.f, 2.f));
                gSprite.setPosition(sf::Vector2f(x * scale, y * scale));
                window.draw(gSprite);
            }
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
};

#endif //FOOTBALLFIELD_H
