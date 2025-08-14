//
// Created by jkirc on 8/13/2025.
//

#ifndef FOOTBALLFIELDRENDERER_H
#define FOOTBALLFIELDRENDERER_H
#include "FootballField.h"
#include "../../../util/Logger.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

class FootballFieldRenderer {
    FootballFieldRenderer(FootballField& field) : field(field) {
        std::string errorMessage = "Unable to load tile texture for field";
        std::string prefix = "../assets/texture/tile/";

        if (!grass.loadFromFile(prefix + "grass_tile.png")) {
            Logger::error(errorMessage, typeid(*this));
        }

        if (!grass.loadFromFile(prefix + "boundary_tile.png")) {
            Logger::error(errorMessage, typeid(*this));
        }
    }

    void render(double dt, sf::RenderWindow& window) {

    }
private:
    sf::Texture grass;
    sf::Texture boundary;

    FootballField& field;
};

#endif //FOOTBALLFIELDRENDERER_H
