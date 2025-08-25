//
// Created by jkirc on 8/9/2025.
//

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "config/Config.h"
#include "scene/Scene.h"
#include "scene/TestScene.h"
#include "scene/football/FootballScene.h"

class Game {
public:
    static constexpr int WINDOW_WIDTH = 1280u;
    static constexpr int WINDOW_HEIGHT = 720u;

    Game() :
    window(sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Football!!")) {
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
                    //This mapPixelToCoords scales it with current view
                    sf::Vector2f mapped = window.mapPixelToCoords({mouseButtonPressed->position.x, mouseButtonPressed->position.y});
                    auto pos = Vector2D(mapped.x, mapped.y);
                    currentScene->mousePressed(mouseButtonPressed->button, pos);
                }
            }


            window.clear();

            //Game Logic
            currentScene->tick(deltaTime);
            //Render Logic
            currentScene->render(deltaTime, window);

            if (Config::IS_DEBUG_MODE) {
                debugCamera();
            }

            window.display();
        }
    }

private:
    sf::RenderWindow window;
    Scene* currentScene;

    double debugX = 0;
    double debugY = 0;
    double debugSpeed = 3;

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
        sf::View testing = sf::View(sf::FloatRect(sf::Vector2f(debugX, debugY), sf::Vector2f(WINDOW_WIDTH * 0.8, FieldConstants::FIELD_WIDTH_PX)));
        window.setView(testing);
    }
};

#endif //GAME_H
