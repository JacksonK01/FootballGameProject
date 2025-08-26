//
// Created by jkirc on 8/26/2025.
//

#include "Vector2D.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

void Vector2D::render(sf::RenderWindow &window, const Vector2D &origin) const {
    render(window, origin, sf::Color::Red);
}

void Vector2D::render(sf::RenderWindow &window, const Vector2D &origin, const sf::Color &color) const {
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

void Vector2D::renderPointed(sf::RenderWindow &window, const Vector2D &origin, const sf::Color &color) const {
    // Draw line from origin → tip
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(static_cast<float>(origin.getX()), static_cast<float>(origin.getY())), color),
        sf::Vertex(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), color)
    };
    window.draw(line, 2, sf::PrimitiveType::Lines);

    // Draw arrowhead as a small triangle
    float arrowSize = 10.0f; // length of arrowhead
    float arrowWidth = 6.0f; // width of the base

    // Compute the direction vector from origin to tip
    sf::Vector2f dir(static_cast<float>(x - origin.getX()), static_cast<float>(y - origin.getY()));
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length == 0) return; // avoid division by zero

    // Normalize direction
    dir.x /= length;
    dir.y /= length;

    // Perpendicular vector for width
    sf::Vector2f perp(-dir.y, dir.x);

    // Compute the three points of the triangle
    sf::Vector2f tip(static_cast<float>(x), static_cast<float>(y));
    sf::Vector2f left = tip - dir * arrowSize + perp * (arrowWidth / 2.0f);
    sf::Vector2f right = tip - dir * arrowSize - perp * (arrowWidth / 2.0f);

    sf::ConvexShape arrowHead;
    arrowHead.setPointCount(3);
    arrowHead.setPoint(0, tip);
    arrowHead.setPoint(1, left);
    arrowHead.setPoint(2, right);
    arrowHead.setFillColor(color);

    window.draw(arrowHead);
}
