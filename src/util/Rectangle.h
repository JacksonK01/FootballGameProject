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
        Rectangle(double x, double y, double width, double height) {
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

    private:
        double x, y;
        double width, height;
    };
}
#endif // RECTANGLE_H
