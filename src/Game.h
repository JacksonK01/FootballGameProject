//
// Created by jkirc on 8/9/2025.
//

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "scene/Scene.h"
#include "scene/TestScene.h"

class Game {
public:
    Game() :
    window(sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Game")) {
        currentScene = new TestScene();
    }

    void run() {
        window.setFramerateLimit(60);

        sf::Clock clock;

        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();

            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    // Gets triggered when window WANTS to close
                    // Could be useful for saving data before exiting the game
                    window.close();
                }
            }

            window.clear();

            //Game Logic
            currentScene->tick(deltaTime);
            //Render Logic
            currentScene->render(deltaTime, window);

            //TODO replace this with better solution
            if (isButtonPressed(sf::Mouse::Button::Left)) {
                const sf::Vector2i mousePos = sf::Mouse::getPosition(this->window);
                currentScene->onMouseClickEvent(Vector2D(mousePos.x, mousePos.y));
            }

            window.display();
        }
    }

private:
    sf::RenderWindow window;
    Scene* currentScene;
};

#endif //GAME_H
