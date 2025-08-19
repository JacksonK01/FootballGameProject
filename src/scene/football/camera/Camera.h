//
// Created by jkirc on 8/18/2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "../entity/Entity.h"
#include "SFML/Graphics/View.hpp"

//This is basically a wrapper for view
class Camera {
public:
    Camera() {}
private:
    sf::View view;
    double x, y = 0;
    Entity* toFollow;
};

#endif //CAMERA_H
