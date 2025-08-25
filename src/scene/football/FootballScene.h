//
// Created by jkirc on 8/10/2025.
//

#ifndef FOOTBALLSCENE_H
#define FOOTBALLSCENE_H
#include "../Scene.h"
#include <SFML/Graphics.hpp>

#include "../../event/EventBus.h"
#include "controller/PlayerController.h"
#include "field/FootballField.h"

//Add events to prevent too much cross object coupling.
class FootballScene : public Scene {
public:
    explicit FootballScene(sf::RenderWindow& window) : Scene(window), eventBus(), field(eventBus), player1(nullptr) {
        inputManager.createKeyPressedEvent(sf::Keyboard::Key::W, [this]() {
            direction = direction + Vector2D(0, -1);
        });

        inputManager.createKeyPressedEvent(sf::Keyboard::Key::S, [this]() {
            direction = direction + Vector2D(0, 1);
        });

        inputManager.createKeyPressedEvent(sf::Keyboard::Key::A, [this]() {
            direction = direction + Vector2D(-1, 0);
        });

        inputManager.createKeyPressedEvent(sf::Keyboard::Key::D, [this]() {
            direction = direction + Vector2D(1, 0);
        });

        inputManager.createMouseButtonEvent(sf::Mouse::Button::Left, [this, &window](const Vector2D& pos) {
            player1.onMouseClicked(pos);
        });

        inputManager.createKeyPressedEvent(sf::Keyboard::Key::Space, [this]() {
            field.snapBall();
        });

        player1.setLinkedEntity(field.getTeamOffense().getDepthChart().getStartingQB());

        eventBus.subscribe<PassCaughtEvent>([this](PassCaughtEvent& event) {
            player1.setLinkedEntity(event.wr);
        });
    };

    void tick(double dt) override {
        Scene::tick(dt);

        if (direction != Vector2D(0, 0)) {
            player1.directionalInput(direction);
            direction = {0, 0};
        }

        field.tick(dt);
    }

    void render(double dt, sf::RenderWindow& window) override {
        field.render(dt, window);
    }

    void mousePressed(sf::Mouse::Button button, const Vector2D& pos) override {
        inputManager.onMousePressed(button, FieldConstants::toYards(pos));
    };

private:
    EventBus eventBus;
    FootballField field;
    PlayerController player1;

    //Used so the input can compound
    Vector2D direction;
};

#endif //FOOTBALLSCENE_H
