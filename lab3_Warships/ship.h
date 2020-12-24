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
    size_t health;
    std::vector<bool> cells;
public:
    int x;
    int y;
    route direction;
    Ship(int _x, int _y, route _direction, size_t _size);
    size_t getSize() const;
    size_t getHealth() const;
    std::vector<std::pair<int, int>> where() const;
    bool damage(int _x, int _y);
};

