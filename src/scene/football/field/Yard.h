//
// Created by jkirc on 8/13/2025.
//

#ifndef YARD_H
#define YARD_H
#include "../../../util/math/Vector2D.h"

//This will be the standard unit for knowing any place on the field.
class Yard {
public:
    //Every 32 pixels will equal 1 yard.
    static constexpr int PIXEL_PER_YARD = 21;


    Yard(double x, double y, double amount): x(x), y(y), amount(amount) {}

    static Yard amountOfYards(const Vector2D& origin, const Vector2D& destination) {
        double d = (origin - destination).length();

        return Yard(origin.getX(), origin.getY(), d);
    }

    static Yard toYards(double distanec) {
        return Yard(0, 0, distanec / PIXEL_PER_YARD);
    }

    static double toYardsInPixel(double amount) {
        return amount * PIXEL_PER_YARD;
    }

    double toPixels() {
        return amount * PIXEL_PER_YARD;
    }

    Vector2D getPos() {
        return Vector2D(x, y);
    }

    double getAmountOfYards() {
        return amount;
    }

private:
    const double x;
    const double y;
    const double amount;
};

#endif //YARD_H
