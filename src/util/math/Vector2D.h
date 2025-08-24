#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <ostream>
#include <stdexcept>

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

    void render(sf::RenderWindow& window, const Vector2D& origin) const {
        render(window, origin, sf::Color::Red);
    }

    void render(sf::RenderWindow& window, const Vector2D& origin, const sf::Color& color) const {
        // line from origin → tip
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(static_cast<float>(origin.getX()), static_cast<float>(origin.getY())), color),
            sf::Vertex(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), color)
        };

        window.draw(line, 2, sf::PrimitiveType::Lines);

        // circle at the tip
        float radius = 5.0f;
        sf::CircleShape tip(radius);
        tip.setFillColor(color);

        // center the circle on the tip
        tip.setOrigin(sf::Vector2f(radius, radius));
        tip.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));

        window.draw(tip);
    }


    // Output stream (friend function)
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

#endif // VECTOR2D_H
