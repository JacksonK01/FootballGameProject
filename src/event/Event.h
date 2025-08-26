//
// Created by jkirc on 8/10/2025.
//

#pragma once

struct Event {
    virtual ~Event() = default;
    int callbacks = 0;
};

