//
// Created by jkirc on 8/10/2025.
//
#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

namespace util {
#ifndef RECTANGLE_H
#define RECTANGLE_H

    class Rectangle {
    public:
        Rectangle(const double width, const double height) {
            this->x = 0;
            this->y = 0;
            this->width = width;
            this->height = height;
        }

        Rectangle(const double x, const double y, const double width, const double height) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }

        [[nodiscard]] double getX() const { return this->x; }
        [[nodiscard]] double getY() const { return this->y; }
        [[nodiscard]] double getWidth() const { return this->width; }
        [[nodiscard]] double getHeight() const { return this->height; }

        void setX(const double& x) { this->x = x; }
        void setY(const double& y) { this->y = y; }
        void setWidth(const double& width) { this->width = width; }
        void setHeight(const double& height) { this->height = height; }

        [[nodiscard]] Rectangle inflate(double factor) const {
            double newWidth  = width + factor;
            double newHeight = height + factor;
            double newX = x - factor * 0.5;
            double newY = y - factor * 0.5;

            return {newX, newY, newWidth, newHeight};
        }

        void centerToPos(const Vector2D& pos) {
            this->x = pos.getX() - (width * 0.5);
            this->y = pos.getY() - (height * 0.5);
        }

        [[nodiscard]] bool intersects(const Rectangle& other) const {
            const bool doesOverlap =
                x > other.x + other.width ||
                other.x > x + width ||
                y > other.y + other.height ||
                other.y > y + height;

            return !doesOverlap;
        }

        // ---------- render method ----------
        void render(sf::RenderWindow& window) const {
            sf::Color color = sf::Color::Green;
            sf::RectangleShape shape(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
            shape.setFillColor(sf::Color::Transparent); // transparent fill
            shape.setOutlineColor(color);               // outline color
            shape.setOutlineThickness(2.f);            // outline thickness
            shape.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
            window.draw(shape);
        }

        //Created a sprite based on this rectangle, scaled with the rectangle
        [[nodiscard]] sf::Sprite getSpriteFromRectangle(const sf::Texture& image) const {
            sf::Sprite sprite(image);

            sprite.setScale(sf::Vector2f(static_cast<float>(width) / image.getSize().x, static_cast<float>(height) / image.getSize().y));

            sprite.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));

            return std::move(sprite);
        }

        //Creates a sprite the size of rectangle
        [[nodiscard]] sf::Sprite getSpriteFromRectSize(const sf::Texture& image) const {
            sf::Sprite sprite(image);

            sprite.setTextureRect(sf::IntRect(sf::Vector2(0, 0), sf::Vector2(static_cast<int>(width), static_cast<int>(height))));

            sprite.setPosition(sf::Vector2f(static_cast<float>(this->x), static_cast<float>(this->y)));

            return std::move(sprite);
        }

    private:
        double x, y;
        double width, height;
    };
}
#endif // RECTANGLE_H
