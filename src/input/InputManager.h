//
// Created by jkirc on 5/28/2025.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <vector>
#include <functional>

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

        keyPressedEvents.emplace_back(event);
    }

    void tick() {
        std::for_each(keyPressedEvents.begin(), keyPressedEvents.end(), [](auto& event) {
            event();
        });
    };

private:
    std::vector<std::function<void()>> keyPressedEvents;
};


#endif //INPUTMANAGER_H
