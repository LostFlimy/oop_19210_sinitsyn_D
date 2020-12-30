#include "ship.h"

Ship::Ship(int _x, int _y, Ship::route _direction, size_t _size) {
    this->x = _x;
    this->y = _y;
    this->direction = _direction;
    this->size = _size;
    this->health = _size;
}

size_t Ship::getHealth() const {
    return health;
}

size_t Ship::getSize() const {
    return size;
}

bool Ship::damage(int _x, int _y) {
    if(direction == route::X){
        if(_y != this->y) {
            return false;
        }
        if(_x >= x + size){
            return false;
        }
        if(_x < x){
            return false;
        }
        health -= 1;
        return true;
    }
    if(direction == route::Y){
        if(_x != this->x) {
            return false;
        }
        if(_y >= y + size){
            return false;
        }
        if(_y < y) {
            return false;
        }
        health -= 1;
        return true;
    }
    return true;
}

std::vector<std::pair<int, int>> Ship::where() const{
    std::vector<std::pair<int, int>> res(size);
    if(direction == route::X) {
        for(int i = 0; i < size; ++i){
            res[i].first = this->x + i;
            res[i].second = this->y;
        }
    }
    if(direction == route::Y) {
        for(int i = 0; i < size; ++i){
            res[i].first = this->x;
            res[i].second = this->y + i;
        }
    }
    return res;
}
