#pragma once
#include <vector>
#include <map>

class Ship {
public:
    enum class route{
        X, Y
    };
protected:
    size_t size;
    int x;
    int y;
    size_t health;
    route direction;
    std::vector<bool> cells;
public:
    Ship(int _x, int _y, route _direction, size_t _size);
    size_t getSize() const;
    size_t getHealth() const;
    std::vector<std::pair<int, int>> where() const;
    bool damage(int _x, int _y);
};

