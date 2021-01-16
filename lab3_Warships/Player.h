#pragma once
#include "ship.h"
#include "cell.h"
#include <map>
#include <string>
#include <ctime>
#include <iostream>
#include <regex>
#include <math.h>
#include <string.h>

class Player {
protected:
    Player();
    bool CheckShip(int x, int y, int direct, size_t size);
    size_t count_of_ships;
public:
    std::string name;
    std::vector<std::vector<Cell>> enemy_field;
    std::vector<std::vector<Cell>> your_field;
    std::vector<Ship> your_ships;
    size_t getCountOfShips();
    virtual std::pair<int, int> shoot() = 0;
    virtual bool place_ship(size_t size) = 0;
};

class HardBot : public Player {
private:
    int last_x1;
    int last_y1;
    int last_x2;
    int last_y2;
    bool last_hit;
public:
    HardBot(size_t count_of_ships);
    std::pair<int, int> shoot();
    bool place_ship(size_t size);
};

class Human : public Player {
public:
    Human(size_t count_of_ships);
    std::pair<int, int> shoot();
    bool place_ship(size_t size);
};

class EasyBot : public Player {
public:
    EasyBot(size_t count_of_ships);
    std::pair<int, int> shoot();
    bool place_ship(size_t size);
};