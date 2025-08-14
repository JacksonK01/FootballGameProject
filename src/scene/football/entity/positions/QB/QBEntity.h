//
// Created by jkirc on 8/10/2025.
//

#ifndef QBENTITY_H
#define QBENTITY_H
#include "../PositionEntity.h"
#include "../../../../../util/Logger.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

//This implementation is purely for practice.
class QBEntity : public PositionEntity {
public:
    QBEntity(Emitter& emitter): PositionEntity(emitter) {
        //Checks if texture does not load
        if (!texture.loadFromFile("../assets/entity/QB.png")) {
            Logger::error("QB unable to load texture", typeid(*this));
        }

        //placeholder value for now.
        this->rating.speed = 5;
        this->rating.throwPower = 100;
    } ;

    void render(double dt, sf::RenderWindow &window) override {
        sf::Sprite qb(texture);
        qb.setPosition(sf::Vector2f(x, y));
        qb.scale(sf::Vector2f(3.f, 3.f));

        window.draw(qb);
    }

    //Possibly remove and replace with a reflection based system to find position
    const std::string getPositionAbbreviation() override {
        return "QB";
    };

    void onMouseClicked(const Vector2D& pos) override {
        if (doesHaveFootball()) {
            ThrownPassEvent event = ThrownPassEvent(*this, pos);
            emitter.emit(event);
        } else {
            Logger::warn("Attempted to throw a pass without a football", typeid(*this));
        }
    };

    void onDirectionalInput(const Vector2D& direction) override {
        this->x += direction.getX() * this->rating.speed;
        this->y += direction.getY() * this->rating.speed;
    };

private:
    sf::Texture texture;
};


#endif //QBENTITY_H
