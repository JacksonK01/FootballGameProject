//
// Created by jkirc on 8/9/2025.
//

#ifndef SCENE_H
#define SCENE_H
#include "../util/math/Vector2D.h"

//Every menu/game will be a scene. For example, the football field is it's own scene, a menu is it's own scene.
class Scene {
public:
    virtual ~Scene() = default;


    //Doing this forces any scene provide their own implementation.
    virtual void tick(double dt) = 0;
    virtual void render(double dt, sf::RenderWindow& window) = 0;
    virtual void onMouseClickEvent(Vector2D pos) = 0;
};

#endif //SCENE_H
