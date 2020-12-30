#pragma once
#include "Handler.h"
#include <memory>

//size of big ship = 4
//size of medium_big ship = 3;
//size of medium_small ship = 2;
//size of small ship = 1;

class Game {
private:
    const size_t size_of_field;
    const size_t count_of_small = 4;
    const size_t count_of_medium_small = 3;
    const size_t count_of_medium_big = 2;
    const size_t count_of_big = 1;
    const size_t count_of_ship = 10;
    std::unique_ptr<Player> plr1;
    std::unique_ptr<Player> plr2;

    // o = CLEAR, x = DAMAGE, w = SHADED, T = SHIP

    std::vector<std::vector<char>> plr1_friend_field;
    std::vector<std::vector<char>> plr1_enemy_field;
    std::vector<std::vector<char>> plr2_friend_field;
    std::vector<std::vector<char>> plr2_enemy_field;
public:
    Game(size_t size_of_field);
    void GameInitial();
    void GameFight();
    void DrawView(size_t number);
    void RestoreInfo();
};

