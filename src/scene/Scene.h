//
// Created by jkirc on 8/9/2025.
//

#ifndef SCENE_H
#define SCENE_H
#include "../input/InputManager.h"
#include "../util/math/Vector2D.h"

//Every menu/game will be a scene. For example, the football field is it's own scene, a menu is it's own scene.
class Scene {
public:
    virtual ~Scene() = default;
    Scene(sf::RenderWindow& window) : inputManager() {};

    //Abstract method with default implementation
    virtual void tick(double dt) {
        inputManager.tick();
    };

    //Abstract Methods, forces an inherter to have it's own implementation.
    virtual void render(double dt, sf::RenderWindow& window) = 0;
    virtual void mousePressed(sf::Mouse::Button button, const Vector2D& pos) = 0;
protected:
    //Each scene has it's own set of inputs. Done for simplicity.
    InputManager inputManager;
};

#endif //SCENE_H
