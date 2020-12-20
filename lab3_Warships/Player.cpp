#include "Player.h"


std::pair<int, int> HardBot::shoot() {
    if(last_hit == true) {
        if (last_x1 == last_x2 && last_y1 == last_y2) {
            if (enemy_field[last_x1 + 1][last_y1].getStatus() == status::CLEAR) {
                return {last_x1 + 1, last_y1};
            }
            if (enemy_field[last_x1 - 1][last_y1].getStatus() == status::CLEAR) {
                return {last_x1 - 1, last_y1};
            }
            if (enemy_field[last_x1][last_y1 + 1].getStatus() == status::CLEAR) {
                return {last_x1, last_y1 + 1};
            }
            if (enemy_field[last_x1][last_y1 - 1].getStatus() == status::CLEAR) {
                return {last_x1, last_y1 - 1};
            }
        } else {
            if (last_x1 == last_x2) {
                if (enemy_field[last_x1][last_y1 - 1].getStatus() == status::CLEAR) {
                    return {last_x1, last_y1 - 1};
                }
                if (enemy_field[last_x2][last_y2 + 1].getStatus() == status::CLEAR) {
                    return {last_x2, last_y2 + 1};
                }
            }
            if (last_y1 == last_y2) {
                if (enemy_field[last_x1 - 1][last_y1].getStatus() == status::CLEAR) {
                    return {last_x1 - 1, last_y1};
                }
                if (enemy_field[last_x2 + 1][last_y2].getStatus() == status::CLEAR) {
                    return {last_x2 + 1, last_y2};
                }
            }
        }
    }
    srand(time(0));
    int x = rand() % 10;
    int y = rand() % 10;
    while(enemy_field[x][y].getStatus() != status::CLEAR){
        x = rand() % 10;
        y = rand() % 10;
    }
    return {x,y};
}

std::pair<int, int> Human::shoot(int x, int y) {
    return {x,y};
}

std::pair<int, int> EasyBot::shoot() {
    srand(time(0));
    int x = rand() % 10;
    int y = rand() % 10;
    while(enemy_field[x][y].getStatus() != status::CLEAR){
        x = rand() % 10;
        y = rand() % 10;
    }
    return {x,y};
}

Player::Player(size_t count_of_ships) {
    this->count_of_ships = count_of_ships;
    for(int i = 0; i < count_of_ships; ++i){
        for(int j = 0; j< count_of_ships; ++j){
            your_field[i][j].setStatus(status::CLEAR);
            enemy_field[i][j].setStatus(status::CLEAR);
        }
    }
}
