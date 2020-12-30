#include "Handler.h"

bool Handler::step(Player &you, Player &enemy) {
    std::pair<int, int> crd = you.shoot();
    while(crd.first == -1 || crd.second == -1) {
        crd = you.shoot();
    }
    bool shoot_is_successful = false;
    int health = 0;
    bool win = false;

    for(int i = 0; i < enemy.count_of_ships; ++i){
        if(enemy.your_ships[i].damage(crd.first, crd.second)) {
            //устанавливаем статус ячейки у противника и союзника
            enemy.your_field[crd.first][crd.second].setStatus(status::DAMAGE);
            you.enemy_field[crd.first][crd.second].setStatus(status::DAMAGE);
            shoot_is_successful = true;

            //(Для HardBot) устанавливаем статус последнего удачного выстрела
            if(!(you.last_hit)) {
                you.last_x1 = crd.first;
                you.last_x2 = crd.first;
                you.last_y1 = crd.second;
                you.last_y2 = crd.second;
                you.last_hit = true;
            }
            else {
                if(crd.first > you.last_x2) {
                    you.last_x2 = crd.first;
                }
                if(crd.first < you.last_x1) {
                    you.last_x1 = crd.first;
                }
                if(crd.second > you.last_y2) {
                    you.last_y2 = crd.second;
                }
                if(crd.second < you.last_y1) {
                    you.last_y1 = crd.second;
                }
            }

            //Если корабль уничтожен, то сбрасываем статус последнего выстрела для HardBot, для всех
            //остальных закрашиваем клетки вокруг этого корабля, в том числе и для HardBot
            if(enemy.your_ships[i].getHealth() == 0) {
                you.last_hit = false;
                you.last_x1 = 100;
                you.last_x2 = 100;
                you.last_y1 = 100;
                you.last_y2 = 100;
                Destroy_ship(you, enemy, i);
            }
        }
        health += enemy.your_ships[i].getHealth();
    }

    if(!shoot_is_successful) {
        enemy.your_field[crd.first][crd.second].setStatus(status::SHADED);
        you.enemy_field[crd.first][crd.second].setStatus(status::SHADED);
    }

    if(health == 0) {
        win = true;
    }
    return win;
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
