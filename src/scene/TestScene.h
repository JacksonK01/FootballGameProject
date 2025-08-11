//
// Created by jkirc on 8/9/2025.
//

#ifndef TESTSCENE_H
#define TESTSCENE_H
#include "Scene.h"

class TestScene : public Scene {
public:
    TestScene(sf::RenderWindow& window): Scene(window) {} ;

    void tick(double dt) override {
        //Vertical Movement
        if (isKeyPressed(sf::Keyboard::Key::W)) {
            this->y -= this->speed;
        }
        if (isKeyPressed(sf::Keyboard::Key::S)) {
            this->y += this->speed;
        }

        //Horizontal Movement
        if (isKeyPressed(sf::Keyboard::Key::D)) {
            this->x += this->speed;
        }
        if (isKeyPressed(sf::Keyboard::Key::A)) {
            this->x -= this->speed;
        }
    };

    void render(double dt, sf::RenderWindow& window) override {
        sf::RectangleShape entityRender(sf::Vector2f(100.0f, 100.0f));
        entityRender.setFillColor(sf::Color::White);
        entityRender.setPosition(sf::Vector2f(x, y));

        window.draw(entityRender);
    };

private:
    //Test player
    int x = 0;
    int y = 0;

    int speed = 10;
};

#endif //TESTSCENE_H
