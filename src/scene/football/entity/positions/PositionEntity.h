//
// Created by jkirc on 8/10/2025.
//

#ifndef POSITIONENTITY_H
#define POSITIONENTITY_H
#include "../Entity.h"
#include "../objects/FootballEntity.h"
#include "rating/Ratings.h"

//This will be the base class to represent a position as an entity. These entities will be built to be controlled by a player or an AI. Will be the
//base class for positions within football I.E. QB, RB, WR, CB.
//Will have base attributes like Stamina, Strength, Awareness, and ETC
//Any position will be able to do anything.
class PositionEntity : public Entity {
public:
    PositionEntity(Emitter& emitter) : emitter(emitter) {};
    //Will become useful, example: A quarterback would return "QB"
    virtual const std::string getPositionAbbreviation() = 0;

    //For inputs from a player controller
    virtual void onMouseClicked(const Vector2D& pos) = 0;
    virtual void onDirectionalInput(const Vector2D& direction) = 0;

    //Returns true if football is successfully removed
    virtual bool removeFootball() {
        if (doesHaveFootball()) {
            football = nullptr;
            return true;
        }
        Logger::warn("This entity had no football to be removed", typeid(*this));
        return false;
    }

    //returns true if football can be given.
    virtual bool giveFootball(FootballEntity* football) {
        if (doesHaveFootball()) {
            return false;
        }

        this->football = football;
        return true;
    }

    //returns true if have football
    virtual bool doesHaveFootball() {
        return this->football;
    }

    Rating getRatings() {
        return rating;
    }

protected:
    Rating rating;
    Emitter& emitter;

    //Meant for only internals
    FootballEntity& getFootball() {
        //Checks if football is not null
        if (!doesHaveFootball()) {
            //This will throw an error if it does not have it.
            Logger::error("Entity tried accessing football when it did not have it.", typeid(*this));
        }
        return *football;
    }

private:
    FootballEntity* football = nullptr;
};

#endif //POSITIONENTITY_H
