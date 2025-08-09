#include <iostream>

#include "Game.h"
#include "util/Logger.h"

int main() {
    Game game = Game();
    game.run();
    Logger::warn("Game has Ended");
    return 0;
}
