#pragma once
#include "Handler.h"


class Game {
private:
    Player& plr1;
    Player& plr2;

    // o = CLEAR, x = DAMAGE, w = SHADED, T = SHIP

    std::vector<std::vector<char>> plr1_friend_field;
    std::vector<std::vector<char>> plr1_enemy_field;
    std::vector<std::vector<char>> plr2_friend_field;
    std::vector<std::vector<char>> plr2_enemy_field;
public:
    Game(Player& player1, Player& player2, size_t size_of_field);
    void GameInitial(size_t count_of_ships);


};

