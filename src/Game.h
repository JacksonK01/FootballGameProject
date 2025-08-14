//
// Created by jkirc on 8/9/2025.
//

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "scene/Scene.h"
#include "scene/TestScene.h"
#include "scene/football/FootballScene.h"

class Game {
public:
    //This enables a debug camera
    static constexpr bool IS_DEBUG_MODE = false;

    Game() :
    window(sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Football!!")) {
        window.setKeyRepeatEnabled(false);
        currentScene = new FootballScene(window);
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

                //Will probably need to switch how input system works, see documentation here:
                //https://www.sfml-dev.org/tutorials/3.0/window/events/#the-keypressed-and-keyreleased-events
                if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    currentScene->mousePressed(mouseButtonPressed->button, Vector2D(mouseButtonPressed->position.x, mouseButtonPressed->position.y));
                }
            }


            window.clear();

            if (IS_DEBUG_MODE) {
                debugCamera();
            }

            //Game Logic
            currentScene->tick(deltaTime);
            //Render Logic
            currentScene->render(deltaTime, window);

            window.display();
        }
    }

private:
    sf::RenderWindow window;
    Scene* currentScene;

    int debugX = 0;
    int debugY = 0;
    int debugSpeed = 6;

    void debugCamera() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            debugY -= debugSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            debugY += debugSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            debugX += debugSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            debugX -= debugSpeed;
        }

        //TODO this is just for testing. Don't leave this in here long term.
        sf::View testing = sf::View(sf::Vector2f(debugX, debugY), sf::Vector2f(1280.f, 720.f));
        window.setView(testing);
    }
};

#endif //GAME_H
