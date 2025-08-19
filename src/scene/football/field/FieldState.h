//
// Created by jkirc on 8/18/2025.
//

#ifndef FIELDSTATE_H
#define FIELDSTATE_H

//Enum for deciding what a FootballField should do
enum FieldState {
    //Get playcall for player
    PLAY_CALLING,
    //Where motion will happen
    PRE_SNAP,
    //Where the play actually runs
    SNAP,
    //To signal a play is over and reset, possible run stat trackers
    POST_SNAP
};

#endif //FIELDSTATE_H
