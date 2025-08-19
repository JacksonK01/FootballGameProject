//
// Created by jkirc on 8/18/2025.
//

#ifndef UTIL_H
#define UTIL_H

#include <string>

#include "Position.h"

inline std::string positionToString(Position position) {
    switch (position) {
        case QB:   return "QB";
        case WR:   return "WR";
        case RB:   return "RB";
        case OT:   return "OT";
        case OG:   return "OG";
        case C:    return "C";
        case TE:   return "TE";
        case EDGE: return "EDGE";
        case DT:   return "DT";
        case CB:   return "CB";
        case MIKE: return "MIKE";
        case SAM:  return "SAM";
        case WILL: return "WILL";
        case SS:   return "SS";
        case FS:   return "FS";
        default:   return "UNKNOWN";
    }
}

#endif //UTIL_H
