//
// Created by jkirc on 8/10/2025.
//

#pragma once

class Vector2D;

namespace sf {
    class RenderWindow;
    class Color;
    class Texture;
    class Sprite;
}

namespace util {
    #pragma once

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

        void centerToPos(const Vector2D& pos);

        [[nodiscard]] bool intersects(const Rectangle& other) const {
            const bool doesOverlap =
                x > other.x + other.width ||
                other.x > x + width ||
                y > other.y + other.height ||
                other.y > y + height;

            return !doesOverlap;
        }

        // ---------- render method ----------
        void render(sf::RenderWindow& window) const;

        //Created a sprite based on this rectangle, scaled with the rectangle
        [[nodiscard]] sf::Sprite getSpriteFromRectangle(const sf::Texture& image) const;

        //Creates a sprite the size of rectangle
        [[nodiscard]] sf::Sprite getSpriteFromRectSize(const sf::Texture& image) const;

    private:
        double x, y;
        double width, height;
    };
}
