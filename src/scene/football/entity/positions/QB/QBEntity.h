//
// Created by jkirc on 8/10/2025.
//

#ifndef QBENTITY_H
#define QBENTITY_H
#include "../PositionEntity.h"
#include "../../../../../util/Logger.h"
#include "../../objects/FootballEntity.h"
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
    } ;

    void render(double dt, sf::RenderWindow &window) override {
        sf::RectangleShape qb = sf::RectangleShape(sf::Vector2f(200.0f, 200.0f));
        qb.setTexture(&texture);

        window.draw(qb);
    }

    const std::string getPositionAbbreviation() override {
        return "QB";
    };

    void onMouseClicked(const Vector2D pos) override {
        ThrownPassEvent event = ThrownPassEvent(*this, pos);
        emitter.emit(event);
    };

    void onDirectionalInput(const Vector2D direction) override {

    };

private:
    sf::Texture texture;
};


#endif //QBENTITY_H
