//
// Created by jkirc on 5/28/2025.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <vector>
#include <functional>
#include <map>

#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

//Each scene will contain an input manager, that way a scene can pick and choose what kind of inputs they'd like to have.
class InputManager {
public:
    InputManager() = default;

    void createKeyPressedEvent(sf::Keyboard::Key key, const std::function<void()>& action) {
        auto event = [key, action]() {
            if(isKeyPressed(key)) {
                action();
            }
        };

        keyPressedEvents.emplace_back(event);
    }

    void createMouseButtonEvent(sf::Mouse::Button button, const std::function<void()>& action) {
        auto event = [button, action]() {
            if (isButtonPressed(button)) {
                action();
            }
        };

        mousePressedEvents[button] = event;
    }

    void tick() {
        std::for_each(keyPressedEvents.begin(), keyPressedEvents.end(), [](auto& event) {
            event();
        });
    };

    void onMousePressed(sf::Mouse::Button button) {
        for (const auto& pair : mousePressedEvents) {
            auto& butt = pair.first;
            auto& event = pair.second;

            if (butt == button) {
                event();
            }
        }
    }

private:
    std::vector<std::function<void()>> keyPressedEvents;
    std::map<sf::Mouse::Button, std::function<void()>> mousePressedEvents;
};


#endif //INPUTMANAGER_H