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

void Game::GameInitial() {
    plr1.count_of_ships = count_of_ship;
    plr2.count_of_ships = count_of_ship;
    for(int i = 0; i < count_of_big; ++i) {
        if(plr1.name != "easy_bot" && plr1.name != "hard_bot"){
            std::cout << "please choose position for 4-ship" << std::endl;
        }
        bool complete_plr1 = plr1.place_ship(4);
        while(!complete_plr1) {
            complete_plr1 = plr1.place_ship(4);
        }
        bool complete_plr2 = plr2.place_ship(4);
        while(!complete_plr2) {
            complete_plr2 = plr2.place_ship(4);
        }
    }
    for(int i = 0; i < count_of_medium_big; ++i) {
        if(plr1.name != "easy_bot" && plr1.name != "hard_bot"){
            std::cout << "please choose position for 4-ship" << std::endl;
        }
        bool complete_plr1 = plr1.place_ship(3);
        while(!complete_plr1) {
            complete_plr1 = plr1.place_ship(3);
        }
        bool complete_plr2 = plr2.place_ship(3);
        while(!complete_plr2) {
            complete_plr2 = plr2.place_ship(3);
        }
    }
    for(int i = 0; i < count_of_medium_small; ++i) {
        if(plr1.name != "easy_bot" && plr1.name != "hard_bot"){
            std::cout << "please choose position for 4-ship" << std::endl;
        }
        bool complete_plr1 = plr1.place_ship(2);
        while(!complete_plr1) {
            complete_plr1 = plr1.place_ship(2);
        }
        bool complete_plr2 = plr2.place_ship(2);
        while(!complete_plr2) {
            complete_plr2 = plr2.place_ship(2);
        }
    }
    for(int i = 0; i < count_of_small; ++i){
        if(plr1.name != "easy_bot" && plr1.name != "hard_bot"){
            std::cout << "please choose position for 4-ship" << std::endl;
        }
        bool complete_plr1 = plr1.place_ship(1);
        while(!complete_plr1) {
            complete_plr1 = plr1.place_ship(1);
        }
        bool complete_plr2 = plr2.place_ship(1);
        while(!complete_plr2) {
            complete_plr2 = plr2.place_ship(1);
        }
    }
}

void Game::GameFight() {
    Handler hand(plr1, plr2);
    while(true) {
        if(hand.step(plr1, plr2))
            break;
        if(hand.step(plr2, plr1))
            break;
    }
}



