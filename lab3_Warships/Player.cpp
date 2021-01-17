#include "Player.h"


std::pair<int, int> HardBot::shoot() {
    if(last_x1 != -1) {
        if ((last_x1 == last_x2) && (last_y1 == last_y2)) {
            if (enemy_field[last_x1][last_y1].getStatus() == status::DAMAGE) {
                last_hit = true;
            } else {
                last_hit = false;
            }
        }
        if (last_x1 != last_x2) {
            if (enemy_field[last_x1][last_y1].getStatus() == status::SHADED) {
                if (((last_x2 < 9) && (enemy_field[last_x2 + 1][last_y1].getStatus() == status::SHADED)) ||
                                                                                            last_x2 == 9) {
                    if ((last_x2 - last_x1 == 1) &&
                        ((last_y1 < 9 && enemy_field[last_x2][last_y1 + 1].getStatus() == status::SHADED) ||
                         last_y1 == 9) &&
                        ((last_y1 > 0 && enemy_field[last_x2][last_y1 - 1].getStatus() == status::SHADED) ||
                         last_y1 == 0)) {
                        last_hit = false;
                    }
                    if ((last_x2 - last_x1 > 1)) {
                        last_hit = false;
                    }
                    if ((last_x2 - last_x1 == 1) &&
                        ((last_y1 < 9 && enemy_field[last_x2][last_y1 + 1].getStatus() == status::CLEAR) ||
                         (last_y1 > 0 && enemy_field[last_x2][last_y1 - 1].getStatus() == status::CLEAR))) {
                        last_x1 = last_x2;
                        last_hit = true;
                    }
                } else {
                    if (last_x2 - last_x1 == 1) {
                        last_x1 = last_x2;
                        last_hit = true;
                    }
                    if (last_x2 - last_x1 > 1) {
                        last_x1++;
                        last_hit = true;
                    }
                }
            }
            if (enemy_field[last_x2][last_y1].getStatus() == status::SHADED) {
                if (((last_x1 > 0) && (enemy_field[last_x1 - 1][last_y1].getStatus() == status::SHADED)) ||
                    last_x1 == 0) {
                    if ((last_x2 - last_x1 == 1) &&
                        ((last_y1 < 9 && enemy_field[last_x1][last_y1 + 1].getStatus() == status::SHADED) ||
                         last_y1 == 9) &&
                        ((last_y1 > 0 && enemy_field[last_x1][last_y1 - 1].getStatus() == status::SHADED) ||
                         last_y1 == 0)) {
                        last_hit = false;
                    }
                    if ((last_x2 - last_x1 > 1)) {
                        last_hit = false;
                    }
                    if ((last_x2 - last_x1 == 1) &&
                        ((last_y1 < 9 && enemy_field[last_x1][last_y1 + 1].getStatus() == status::CLEAR) ||
                         (last_y1 > 0 && enemy_field[last_x1][last_y1 - 1].getStatus() == status::CLEAR))) {
                        last_x2 = last_x1;
                        last_hit = true;
                    }
                } else {
                    if (last_x2 - last_x1 == 1) {
                        last_x2 = last_x1;
                        last_hit = true;
                    }
                    if (last_x2 - last_x1 > 1) {
                        last_x2--;
                        last_hit = true;
                    }
                }
            }
        }
        if (last_y1 != last_y2) {
            if (enemy_field[last_x1][last_y1].getStatus() == status::SHADED) {
                if (((last_y2 < 9) && (enemy_field[last_x2][last_y2 + 1].getStatus() == status::SHADED)) ||
                    last_y2 == 9) {
                    if ((last_y2 - last_y1 == 1) &&
                        ((last_x1 < 9 && enemy_field[last_x1 + 1][last_y2].getStatus() == status::SHADED) ||
                         last_x1 == 9) &&
                        ((last_x1 > 0 && enemy_field[last_x1 - 1][last_y2].getStatus() == status::SHADED) ||
                         last_x1 == 0)) {
                        last_hit = false;
                    }
                    if ((last_y2 - last_y1 > 1)) {
                        last_hit = false;
                    }
                    if ((last_y2 - last_y1 == 1) &&
                        ((last_x1 < 9 && enemy_field[last_x1 + 1][last_y2].getStatus() == status::CLEAR) ||
                         (last_x1 > 0 && enemy_field[last_x1 - 1][last_y2].getStatus() == status::CLEAR))) {
                        last_y1 = last_y2;
                        last_hit = true;
                    }
                } else {
                    if (last_y2 - last_y1 == 1) {
                        last_y1 = last_y2;
                        last_hit = true;
                    }
                    if (last_y2 - last_y1 > 1) {
                        last_y1++;
                        last_hit = true;
                    }
                }
            }
            if (enemy_field[last_x1][last_y2].getStatus() == status::SHADED) {
                if (((last_y1 > 0) && (enemy_field[last_x1][last_y1 - 1].getStatus() == status::SHADED)) ||
                    last_y1 == 0) {
                    if ((last_y2 - last_y1 == 1) &&
                        ((last_x1 < 9 && enemy_field[last_x1 + 1][last_y1].getStatus() == status::SHADED) ||
                         last_x1 == 9) &&
                        ((last_x1 > 0 && enemy_field[last_x1 - 1][last_y1].getStatus() == status::SHADED) ||
                         last_x1 == 0)) {
                        last_hit = false;
                    }
                    if ((last_y2 - last_y1 > 1)) {
                        last_hit = false;
                    }
                    if ((last_y2 - last_y1 == 1) &&
                        ((last_x1 < 9 && enemy_field[last_x1 + 1][last_y1].getStatus() == status::CLEAR) ||
                         (last_y1 > 0 && enemy_field[last_x1 - 1][last_y1].getStatus() == status::CLEAR))) {
                        last_y2 = last_y1;
                        last_hit = true;
                    }
                } else {
                    if (last_y2 - last_y1 == 1) {
                        last_y2 = last_y1;
                        last_hit = true;
                    }
                    if (last_y2 - last_y1 > 1) {
                        last_y2--;
                        last_hit = true;
                    }
                }
            }
        }
    }
    if(last_hit == true) {
        if (last_x1 == last_x2 && last_y1 == last_y2) {
            if ((last_x1 < 9) && (enemy_field[last_x1 + 1][last_y1].getStatus() == status::CLEAR)) {
                last_x2 = last_x1 + 1;
                return {last_x2, last_y1};
            }
            if ((last_x1 > 0) && (enemy_field[last_x1 - 1][last_y1].getStatus() == status::CLEAR)) {
                last_x2 = last_x1;
                last_x1 = last_x1 - 1;
                return {last_x1, last_y1};
            }
            if ((last_y1 < 9) && (enemy_field[last_x1][last_y1 + 1].getStatus() == status::CLEAR)) {
                last_y2 = last_y1 + 1;
                return {last_x1, last_y2};
            }
            if ((last_y1 > 0) && (enemy_field[last_x1][last_y1 - 1].getStatus() == status::CLEAR)) {
                last_y2 = last_y1;
                last_y1 = last_y1 - 1;
                return {last_x1, last_y1};
            }
        } else {
            if (last_x1 == last_x2) {
                if ((last_y1 > 0) && (enemy_field[last_x1][last_y1 - 1].getStatus() == status::CLEAR)) {
                    last_y1 = last_y1 - 1;
                    return {last_x1, last_y1};
                }
                if ((last_y2 < 9) && (enemy_field[last_x2][last_y2 + 1].getStatus() == status::CLEAR)) {
                    last_y2 = last_y2 + 1;
                    return {last_x2, last_y2};
                }
            }
            if (last_y1 == last_y2) {
                if ((last_x1 > 0) && (enemy_field[last_x1 - 1][last_y1].getStatus() == status::CLEAR)) {
                    last_x1 = last_x1 - 1;
                    return {last_x1, last_y1};
                }
                if ((last_x2 < 9) && (enemy_field[last_x2 + 1][last_y2].getStatus() == status::CLEAR)) {
                    last_x2 = last_x2 + 1;
                    return {last_x2, last_y2};
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
    last_x1 = x;
    last_x2 = x;
    last_y1 = y;
    last_y2 = y;
    last_hit = false;
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
    last_x1 = -1;
    last_x2 = -1;
    last_y1 = -1;
    last_y2 = -1;
    last_hit = false;
}

bool HardBot::place_ship(size_t size) {
    srand(time(0));
    int x = rand() % 10;
    int y = rand() % 10;
    int direct = rand() % 2;
    if((x + direct * (size - 1)) > 9 || (y + ((direct + 1) % 2) * (size - 1)) > 9)
        return false;
    for(int i = 0; i < size; ++i){
        if(your_field[x + i * direct][y + i*((direct + 1) % 2)].getStatus() == status::SHIP){
            return false;
        }
    }
    if(CheckShip(x, y, direct, size)) {
        return false;
    }
    for(int i = 0; i < size; ++i) {
        your_field[x + i * direct][y + i*((direct + 1) % 2)].setStatus(status::SHIP);
    }
    Ship::route direction = ((direct == 1)? (Ship::route::X) : (Ship::route::Y));
    your_ships.push_back(Ship(x, y, direction, size));
    return true;
}

std::pair<int, int> Human::shoot() {
    std::string strx, stry;
    int x(-1), y(-1);
    std::string str;
    std::cin >> str;
    std::regex rx("([A-J])([0-9]+)");
    std::cmatch result;
    if(std::regex_search(str.c_str(), result, rx)) {
        std::string strx = result[1];
        std::string stry = result[2];
        x = (int)strx[0] - (int)'A';
        if(stry.length() == 1) {
            y = (int)stry[0] - (int)('1');
        }
        if(stry.length() == 2) {
            if(stry[0] == '1' && stry[1] == '0') {
                y = 9;
            }
        }
    } else {
        std::cout << "Incorrect input, try again" << std::endl;
        return {-1, -1};
    }
    if(y == -1 || x == -1) {
        return {-1, -1};
    }
    return {y,x};
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

bool Human::place_ship(size_t size) {
    int x1, x2, y1, y2;
    char _y1, _y2;
    std::cin >> _y1 >> x1 >> _y2 >> x2;
    if (std::cin.fail())
    {
        std::cout << "Incorrect input" << std::endl;

        std::cin.clear();

        // From Eric's answer (thanks Eric)
        // discard 'bad' character(s)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    y1 = _y1 - 'A';
    y2 = _y2 - 'A';
    x1--;
    x2--;
    if(x1 > x2){
        int k = x1;
        x1 = x2;
        x2 = k;
    }
    if(y1 > y2){
        int k = y1;
        y1 = y2;
        y2 = k;
    }

    int direct = ((x1 < x2) ? 1 : 0);
    if(((x2 - x1) >= size) || ((y2 - y1) >= size)){
        std::cout << "Incorrect input" << std::endl;
        return false;
    }
    if((x1 + direct * (size - 1)) > 9 || (y1 + ((direct + 1) % 2) * (size - 1)) > 9) {
        std::cout << "Incorrect input" << std::endl;
        return false;
    }
    for(int i = 0; i < size; ++i){
        if(your_field[x1 + i * direct][y1 + i * ((direct + 1) % 2)].getStatus() == status::SHIP){
            std::cout << "Incorrect input" << std::endl;
            return false;
        }
    }
    for(int i = 0; i < size; ++i){
        if(CheckShip(x1, y1, direct, size)) {
            std::cout << "Incorrect input" << std::endl;
            return false;
        }
    }
    for(int i = 0; i < size; ++i) {
        your_field[x1 + i * direct][y1 + i*((direct + 1) % 2)].setStatus(status::SHIP);
    }
    Ship::route direction = ((direct == 1)? (Ship::route::X) : (Ship::route::Y));
    your_ships.push_back(Ship(x1, y1, direction, size));
    return true;
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

bool EasyBot::place_ship(size_t size) {
    srand(time(0));
    int x = rand() % 10;
    int y = rand() % 10;
    int direct = rand() % 2;
    if((x + direct * (size - 1)) > 9 || (y + ((direct + 1) % 2) * (size - 1)) > 9)
        return false;
    for(int i = 0; i < size; ++i){
        if(your_field[x + i * direct][y + i*((direct + 1) % 2)].getStatus() == status::SHIP){
            return false;
        }
    }
    if(CheckShip(x, y, direct, size)) {
        return false;
    }
    for(int i = 0; i < size; ++i) {
        your_field[x + i * direct][y + i*((direct + 1) % 2)].setStatus(status::SHIP);
    }
    Ship::route direction = ((direct == 1)? (Ship::route::X) : (Ship::route::Y));
    your_ships.push_back(Ship(x, y, direction, size));
    return true;
}

Player::Player() {
    your_field.resize(10);
    for(int i = 0; i < 10; ++i) {
        your_field[i].resize(10);
    }
    enemy_field.resize(10);
    for(int i = 0; i < 10; ++i) {
        enemy_field[i].resize(10);
    }
}

bool Player::CheckShip(int x, int y, int direct, size_t size) {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < your_ships.size(); ++j) {
            std::vector<std::pair<int, int>> coord(your_ships[j].getSize());
            coord = your_ships[j].where();
            for(const auto& a : coord) {
                if(abs(x + i * direct - a.first) + abs(y + i * ((direct + 1) % 2) - a.second) <= 1) {
                    return true;
                }
            }
        }
    }
    if( ((x > 0) && (y > 0) && (your_field[x - 1][y - 1].getStatus() == status::SHIP)) ||
        ((x > 0) && (y + (size - 1) * ((direct + 1) % 2) < 9) && (your_field[x - 1][y + (size - 1) * ((direct + 1) % 2) + 1].getStatus() == status::SHIP)) ||
        ((x + (size - 1) * direct < 9) && (y > 0) && (your_field[x + (size - 1) * direct + 1][y - 1].getStatus() == status::SHIP)) ||
        ((x + (size - 1) * direct < 9) && (y + (size - 1) * ((direct + 1) % 2) < 9) && (your_field[x + (size - 1) * direct + 1][y + (size - 1) * ((direct + 1) % 2) + 1].getStatus() == status::SHIP))) {
        return true;
    }
    return false;
}

size_t Player::getCountOfShips() {
    return count_of_ships;
}

status Player::getFriendCell(size_t x, size_t y) {
    return your_field[x][y].getStatus();
}

status Player::getEnemyCell(size_t x, size_t y) {
    return enemy_field[x][y].getStatus();
}

void Player::setFriendCell(size_t x, size_t y, status st) {
    your_field[x][y].setStatus(st);
}

void Player::setEnemyCell(size_t x, size_t y, status st) {
    enemy_field[x][y].setStatus(st);
}

Ship& Player::getShip(size_t index) {
    return your_ships[index];
}

std::string Player::getName() {
    return name;
}







