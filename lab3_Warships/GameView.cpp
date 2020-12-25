#include "GameView.h"

Game::Game(Player &player1, Player &player2, size_t size_of_field) : plr1(player1), plr2(player2) {
    for(int i = 0; i < size_of_field; ++i) {
        for(int j = 0; j < size_of_field; ++j) {
            plr1_enemy_field[i][j] = 'o';
            plr2_enemy_field[i][j] = 'o';
            plr1_friend_field[i][j] = 'o';
            plr2_friend_field[i][j] = 'o';
        }
    }
}

void Game::GameInitial(size_t count_of_ships) {
    for(int i = 0; i < count_of_ships; ++i){
        if()
    }
}

