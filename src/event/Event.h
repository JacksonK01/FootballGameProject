//
// Created by jkirc on 8/10/2025.
//

#ifndef EVENT_H
#define EVENT_H

struct Event {
    virtual ~Event() = default;
    int callbacks = 0;
};

#endif //EVENT_H
