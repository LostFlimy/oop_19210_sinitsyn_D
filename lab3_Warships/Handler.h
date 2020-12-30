#pragma once
#include "Player.h"

class Handler {
public:
    Player& plr1;
    Player& plr2;
public:
    bool step(Player& you, Player& enemy);
    Handler(Player& plr1, Player& plr2);
    void Destroy_ship(Player& you, Player& enemy, int index);
};

