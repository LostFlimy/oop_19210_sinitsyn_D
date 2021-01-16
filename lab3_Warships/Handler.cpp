#include "Handler.h"

bool Handler::step(Player &you, Player &enemy) {
    bool shoot_is_successful = false;

    std::pair<int, int> crd = you.shoot();
    while(crd.first == -1 || crd.second == -1) {
        crd = you.shoot();
    }

    for(int i = 0; i < enemy.getCountOfShips(); ++i){
        if(enemy.your_ships[i].damage(crd.first, crd.second)) {
            //устанавливаем статус ячейки у противника и союзника
            enemy.your_field[crd.first][crd.second].setStatus(status::DAMAGE);
            you.enemy_field[crd.first][crd.second].setStatus(status::DAMAGE);
            shoot_is_successful = true;
            //Если корабль уничтожен, то сбрасываем статус последнего выстрела для HardBot, для всех
            //остальных закрашиваем клетки вокруг этого корабля, в том числе и для HardBot
            if(enemy.your_ships[i].getHealth() == 0) {
                Destroy_ship(you, enemy, i);
            }
        }
    }

    if(!shoot_is_successful) {
        enemy.your_field[crd.first][crd.second].setStatus(status::SHADED);
        you.enemy_field[crd.first][crd.second].setStatus(status::SHADED);
    }

    return shoot_is_successful;
}

Handler::Handler(Player &plr1, Player &plr2) : plr1(plr1), plr2(plr2) {}

void Handler::Destroy_ship(Player &you, Player &enemy, int index) {
    Ship ship = enemy.your_ships[index];
    if(ship.direction == Ship::route::X) {
        if(ship.x > 0) {
            you.enemy_field[ship.x - 1][ship.y].setStatus(status::SHADED);
            enemy.your_field[ship.x - 1][ship.y].setStatus(status::SHADED);
            if(ship.y > 0) {
                you.enemy_field[ship.x - 1][ship.y - 1].setStatus(status::SHADED);
                enemy.your_field[ship.x - 1][ship.y - 1].setStatus(status::SHADED);
            }
            if(ship.y < 9) {
                you.enemy_field[ship.x - 1][ship.y + 1].setStatus(status::SHADED);
                enemy.your_field[ship.x - 1][ship.y + 1].setStatus(status::SHADED);
            }
        }
        for (int i = 0; i < ship.getSize(); ++i) {
            if(ship.where()[i].second > 0) {
                you.enemy_field[ship.where()[i].first][ship.where()[i].second - 1].setStatus(status::SHADED);
                enemy.your_field[ship.where()[i].first][ship.where()[i].second - 1].setStatus(status::SHADED);
            }
            if(ship.where()[i].second < 9) {
                you.enemy_field[ship.where()[i].first][ship.where()[i].second + 1].setStatus(status::SHADED);
                enemy.your_field[ship.where()[i].first][ship.where()[i].second + 1].setStatus(status::SHADED);
            }
        }
        if(ship.x + ship.getSize() - 1 < 9) {
            you.enemy_field[ship.x + ship.getSize()][ship.y].setStatus(status::SHADED);
            enemy.your_field[ship.x + ship.getSize()][ship.y].setStatus(status::SHADED);
            if(ship.y > 0) {
                you.enemy_field[ship.x + ship.getSize()][ship.y - 1].setStatus(status::SHADED);
                enemy.your_field[ship.x + ship.getSize()][ship.y - 1].setStatus(status::SHADED);
            }
            if(ship.y < 9) {
                you.enemy_field[ship.x + ship.getSize()][ship.y + 1].setStatus(status::SHADED);
                enemy.your_field[ship.x + ship.getSize()][ship.y + 1].setStatus(status::SHADED);
            }
        }
    }
    if(ship.direction == Ship::route::Y) {
        if(ship.y > 0) {
            you.enemy_field[ship.x][ship.y - 1].setStatus(status::SHADED);
            enemy.your_field[ship.x][ship.y - 1].setStatus(status::SHADED);
            if(ship.x > 0) {
                you.enemy_field[ship.x - 1][ship.y - 1].setStatus(status::SHADED);
                enemy.your_field[ship.x - 1][ship.y - 1].setStatus(status::SHADED);
            }
            if(ship.x < 9) {
                you.enemy_field[ship.x + 1][ship.y - 1].setStatus(status::SHADED);
                enemy.your_field[ship.x + 1][ship.y - 1].setStatus(status::SHADED);
            }
        }
        for (int i = 0; i < ship.getSize(); ++i) {
            if(ship.where()[i].first > 0) {
                you.enemy_field[ship.where()[i].first - 1][ship.where()[i].second].setStatus(status::SHADED);
                enemy.your_field[ship.where()[i].first - 1][ship.where()[i].second].setStatus(status::SHADED);
            }
            if(ship.where()[i].first < 9) {
                you.enemy_field[ship.where()[i].first + 1][ship.where()[i].second].setStatus(status::SHADED);
                enemy.your_field[ship.where()[i].first + 1][ship.where()[i].second].setStatus(status::SHADED);
            }
        }
        if(ship.y + ship.getSize() - 1 < 9) {
            you.enemy_field[ship.x][ship.y + ship.getSize()].setStatus(status::SHADED);
            enemy.your_field[ship.x][ship.y + ship.getSize()].setStatus(status::SHADED);
            if(ship.x > 0) {
                you.enemy_field[ship.x - 1][ship.y + ship.getSize()].setStatus(status::SHADED);
                enemy.your_field[ship.x - 1][ship.y + ship.getSize()].setStatus(status::SHADED);
            }
            if(ship.x < 9) {
                you.enemy_field[ship.x + 1][ship.y + ship.getSize()].setStatus(status::SHADED);
                enemy.your_field[ship.x + 1][ship.y + ship.getSize()].setStatus(status::SHADED);
            }
        }
    }
}
