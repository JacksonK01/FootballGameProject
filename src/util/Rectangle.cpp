//
// Created by jkirc on 8/26/2025.
//

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "math/Vector2D.h"

#include "Rectangle.h"

void util::Rectangle::render(sf::RenderWindow &window) const {
    sf::Color color = sf::Color::Green;
    sf::RectangleShape shape(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    shape.setFillColor(sf::Color::Transparent); // transparent fill
    shape.setOutlineColor(color);               // outline color
    shape.setOutlineThickness(2.f);            // outline thickness
    shape.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
    window.draw(shape);
}

sf::Sprite util::Rectangle::getSpriteFromRectangle(const sf::Texture &image) const {
    sf::Sprite sprite(image);

    sprite.setScale(sf::Vector2f(static_cast<float>(width) / image.getSize().x, static_cast<float>(height) / image.getSize().y));

    sprite.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));

    return std::move(sprite);
}

sf::Sprite util::Rectangle::getSpriteFromRectSize(const sf::Texture &image) const {
    sf::Sprite sprite(image);

    sprite.setTextureRect(sf::IntRect(sf::Vector2(0, 0), sf::Vector2(static_cast<int>(width), static_cast<int>(height))));

    sprite.setPosition(sf::Vector2f(static_cast<float>(this->x), static_cast<float>(this->y)));

    return std::move(sprite);
}

void util::Rectangle::centerToPos(const Vector2D &pos) {
    this->x = pos.getX() - (width * 0.5);
    this->y = pos.getY() - (height * 0.5);
}




