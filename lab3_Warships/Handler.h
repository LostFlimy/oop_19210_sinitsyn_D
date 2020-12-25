#pragma once
#include "Player.h"

class Handler {
private:
    Player& plr1;
    Player& plr2;
public:
    bool step(Player& you, Player& enemy);
    Handler(Player& plr1, Player& plr2);
    void Destroy_ship(Player& you, Player& enemy, int index, std::pair<int, int> crd);
};

