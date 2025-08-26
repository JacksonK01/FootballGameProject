#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>

namespace sf {
    class RenderWindow;
    class CircleShape;
    class ConvexShape;
    class Color;
}

//Credit: ChatGTP generated this for me
class Vector2D {
private:
    double x;
    double y;

public:
    // Constructors
    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(double x, double y) : x(x), y(y) {}

    // Accessors
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }

    // Core operations
    [[nodiscard]] Vector2D add(const Vector2D& other) const {
        return {x + other.x, y + other.y};
    }
    [[nodiscard]] Vector2D subtract(const Vector2D& other) const {
        return {x - other.x, y - other.y};
    }
    [[nodiscard]] Vector2D multiply(const Vector2D& other) const {
        return {x * other.x, y * other.y};
    }
    [[nodiscard]] Vector2D multiply(const double& factor) const {
        return {x * factor, y * factor};
    }
    [[nodiscard]] Vector2D divide(const double& factor) const {
        return {x / factor, y / factor};
    }
    [[nodiscard]] double length() const {
        return std::sqrt(x * x + y * y);
    }
    [[nodiscard]] double lengthSquared() const {
        return x * x + y * y;
    }
    [[nodiscard]] Vector2D normalize() const {
        double len = length();
        if (len == 0.0) return Vector2D(0.0, 0.0);
        return Vector2D(x / len, y / len);
    }
    [[nodiscard]] Vector2D getAbs() {
        return {std::abs(x), std::abs(y)};
    }

    double dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    double distanceTo(const Vector2D& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Operators
    Vector2D operator+(const Vector2D& other) const {
        return add(other);
    }
    Vector2D operator-(const Vector2D& other) const {
        return subtract(other);
    }
    Vector2D operator*(const Vector2D& other) const {
        return multiply(other);
    }
    bool operator==(const Vector2D& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }
    double operator[](int index) const {
        if (index == 0) return x;
        else if (index == 1) return y;
        throw std::out_of_range("Index out of range for Vector2D");
    }

    // Static helpers
    static Vector2D zero() {
        return Vector2D(0.0, 0.0);
    }
    static Vector2D unitX() {
        return Vector2D(1.0, 0.0);
    }
    static Vector2D unitY() {
        return Vector2D(0.0, 1.0);
    }

    void render(sf::RenderWindow& window, const Vector2D& origin) const;

    void render(sf::RenderWindow& window, const Vector2D& origin, const sf::Color& color) const;

    void renderPointed(sf::RenderWindow& window, const Vector2D& origin, const sf::Color& color) const;

    // Output stream (friend function)
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};
