#pragma once
#include <iostream>
#include <vector>

class ship {
public:
    enum class route{
        X, Y
    };
protected:
    std::size_t size;
    int x;
    int y;
    size_t health;
    route direction;
    std::vector<bool> cells;
public:
    ship(int _x, int _y, route _direction, size_t _size);
    size_t getHealth() const;
    bool damage(int _x, int _y);
};

