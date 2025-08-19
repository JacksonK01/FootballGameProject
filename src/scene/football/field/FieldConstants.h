//
// Created by jkirc on 8/18/2025.
//

#ifndef FIELDCONSTANTS_H
#define FIELDCONSTANTS_H

class FieldConstants {
public:
    static constexpr int PIXEL_PER_YARD = 16;

    static constexpr int FIELD_LENGTH_YARDS = 100;
    static constexpr int FIELD_WIDTH_YARDS = 53;
    static constexpr int YARDS_FOR_FIRST = 10;
    static constexpr int ENTIRE_LENGTH_OF_FIELD = FIELD_LENGTH_YARDS + 2 * YARDS_FOR_FIRST;

    static constexpr int PLAYING_FIELD_LENGTH_PX = FIELD_LENGTH_YARDS * PIXEL_PER_YARD;
    static constexpr int ENDZONE_DEPTH_PX = YARDS_FOR_FIRST * PIXEL_PER_YARD;
    static constexpr int ENTIRE_LENGTH_OF_FIELD_PX = ENTIRE_LENGTH_OF_FIELD * PIXEL_PER_YARD;
    static constexpr int FIELD_WIDTH_PX = FIELD_WIDTH_YARDS * PIXEL_PER_YARD;
};

#endif //FIELDCONSTANTS_H
