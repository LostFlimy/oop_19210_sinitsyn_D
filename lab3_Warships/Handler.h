#pragma once
#include "Player.h"

class Handler {
private:
    Player& plr1;
    Player& plr2;
public:
    bool step(Player& you, Player& enemy);
    Handler(Player& plr1, Player& plr2);
};

