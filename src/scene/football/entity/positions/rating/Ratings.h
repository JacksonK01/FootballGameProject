//
// Created by jkirc on 8/10/2025.
//

#ifndef RATINGS_H
#define RATINGS_H

//Ratings scale from 1-100
//Every player will have a rating in every stat no matter of position
class Rating {
public:
    Rating() {};

    //athletic ratings
    int speed = 1;
    int acceleration = 1;
    int strength = 1;
    int agility = 1; //change of direction
    int stamina = 1;
    int injury = 1;

    //mentals
    int awareness = 1;
    int discipline = 1; //for penalty
    int clutch = 1; //see if a player has ice in their veins.

    //QB
    int passing = 1;
    int throwPower = 1; //velocity on the ball

    //WR, TE, RB, and DBs
    int catching = 1;
    int carrying = 1;

    //OL
    int runBlocking = 1;
    int passBlock = 1;

    //DL, EDGE
    int runShedding = 1; //How quick a DL can shed a run block
    int passRush = 1;

    //DBs
    int manCoverage = 1;
    int zoneCoverage = 1;

    //K, and P
    int kicking = 1;
    int punting = 1;
};

#endif //RATINGS_H
