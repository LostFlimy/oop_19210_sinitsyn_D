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

HardBot::HardBot(size_t count_of_ships) {
    name = "hard_bot";
    this->count_of_ships = count_of_ships;
    for(int i = 0; i < count_of_ships; ++i){
        for(int j = 0; j< count_of_ships; ++j){
            your_field[i][j].setStatus(status::CLEAR);
            enemy_field[i][j].setStatus(status::CLEAR);
        }
    }
}

bool HardBot::place_ship() {
    return false;
}

std::pair<int, int> Human::shoot() {
    std::string strx, stry;
    int x(-1), y(-1);
    std::string str;
    std::cin >> str;
    std::regex rx("([A-J])([1-9]+)");
    std::cmatch result;
    if(std::regex_search(str.c_str(), result, rx)) {
        std::string strx = result[1];
        std::string stry = result[2];
        x = (int)strx[0] - (int)'A';
        if(stry.size() == 1) {
            y = (int)stry[0] - (int)('1');
        }
        if(stry.size() == 2) {
            if(stry[0] == '1' && stry[1] == '0') {
                y = 9;
            }
        }
    }
    if(y == -1 || x == -1) {
        return {-1, -1};
    }
    return {x,y};
}

Human::Human(size_t count_of_ships) {
    this->count_of_ships = count_of_ships;
    for(int i = 0; i < count_of_ships; ++i){
        for(int j = 0; j< count_of_ships; ++j){
            your_field[i][j].setStatus(status::CLEAR);
            enemy_field[i][j].setStatus(status::CLEAR);
        }
    }
}

bool Human::place_ship() {
    return false;
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

EasyBot::EasyBot(size_t count_of_ships) {
    name = "easy_bot";
    this->count_of_ships = count_of_ships;
    for(int i = 0; i < count_of_ships; ++i){
        for(int j = 0; j< count_of_ships; ++j){
            your_field[i][j].setStatus(status::CLEAR);
            enemy_field[i][j].setStatus(status::CLEAR);
        }
    }
}

bool EasyBot::place_ship() {
    return false;
}

Player::Player() {
    last_x1 = 100;
    last_x2 = 100;
    last_y1 = 100;
    last_y2 = 100;
    last_hit = false;
}

