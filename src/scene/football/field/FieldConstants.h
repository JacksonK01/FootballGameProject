//
// Created by jkirc on 8/18/2025.
//

#pragma once

#include "../../../util/Rectangle.h"

class FieldConstants {
public:
    static constexpr int PIXEL_PER_YARD = 16;

    static constexpr int FIELD_LENGTH_YARDS = 100;
    static constexpr int FIELD_WIDTH_YARDS = 53;
    static constexpr int YARDS_FOR_FIRST = 10;
    static constexpr int ENTIRE_LENGTH_OF_FIELD = FIELD_LENGTH_YARDS + (2 * YARDS_FOR_FIRST);

    static constexpr int PLAYING_FIELD_LENGTH_PX = FIELD_LENGTH_YARDS * PIXEL_PER_YARD;
    static constexpr int ENDZONE_DEPTH_PX = YARDS_FOR_FIRST * PIXEL_PER_YARD;
    static constexpr int ENTIRE_LENGTH_OF_FIELD_PX = ENTIRE_LENGTH_OF_FIELD * PIXEL_PER_YARD;
    static constexpr int FIELD_WIDTH_PX = FIELD_WIDTH_YARDS * PIXEL_PER_YARD;

    static double toPixels(const double& yards) {
        return yards * PIXEL_PER_YARD;
    }

    static Vector2D toPixels(const Vector2D& yards) {
        return yards.multiply(PIXEL_PER_YARD);
    }

    static util::Rectangle toPixels(const util::Rectangle& yards) {
        return {yards.getX() * PIXEL_PER_YARD, yards.getY() * PIXEL_PER_YARD, yards.getWidth() * PIXEL_PER_YARD, yards.getHeight() * PIXEL_PER_YARD};
    }

    static double toYards(const double& pixels) {
        return pixels / PIXEL_PER_YARD;
    }

    static Vector2D toYards(const Vector2D& pixels) {
        return pixels.divide(PIXEL_PER_YARD);
    }

    static util::Rectangle toYards(const util::Rectangle& pixels) {
        return {pixels.getX() / PIXEL_PER_YARD, pixels.getY() / PIXEL_PER_YARD, pixels.getWidth() / PIXEL_PER_YARD, pixels.getHeight() / PIXEL_PER_YARD};
    }
};
