#include "ship.h"

ship::ship(int _x, int _y, ship::route _direction, size_t _size) {
    this->x = _x;
    this->y = _y;
    this->direction = _direction;
    this->size = _size;
    this->health = _size;
    cells.resize(_size, true);
}

size_t ship::getHealth() const {
    return health;
}

bool ship::damage(int _x, int _y) {
    if(direction == route::X){
        if(_y != this->y) {
            return false;
        }
        if(_x >= x + size){
            return false;
        }
        cells[_x - x] = false;
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
        cells[_y - y] = false;
        health -= 1;
        return true;
    }
}
