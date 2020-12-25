#include "Handler.h"

bool Handler::step(Player &you, Player &enemy) {
    std::pair<int, int> crd = you.shoot();
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
                Destroy_ship(you, enemy, i, crd);
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

void Handler::Destroy_ship(Player &you, Player &enemy, int index, std::pair<int, int> crd) {
    you.last_hit = false;
    you.last_x1 = 100;
    you.last_x2 = 100;
    you.last_y1 = 100;
    you.last_y2 = 100;
    for(int j = 0; j < enemy.your_ships[index].getSize(); ++index){
        if(enemy.your_ships[index].direction == Ship::route::X) {
            enemy.your_field[enemy.your_ships[index].x + j][crd.second + 1].setStatus(status::SHADED);
            you.enemy_field[enemy.your_ships[index].x + j][crd.second - 1].setStatus(status::SHADED);
            enemy.your_field[enemy.your_ships[index].x + j][crd.second - 1].setStatus(status::SHADED);
            you.enemy_field[enemy.your_ships[index].x + j][crd.second + 1].setStatus(status::SHADED);
        }
        else {
            enemy.your_field[crd.first + 1][enemy.your_ships[index].y + j].setStatus(status::SHADED);
            you.enemy_field[crd.first + 1][enemy.your_ships[index].y + j].setStatus(status::SHADED);
            enemy.your_field[crd.first - 1][enemy.your_ships[index].y + j].setStatus(status::SHADED);
            you.enemy_field[crd.first - 1][enemy.your_ships[index].y + j].setStatus(status::SHADED);
        }
    }
    if(enemy.your_ships[index].direction == Ship::route::X) {
        enemy.your_field[enemy.your_ships[index].x - 1][crd.second].setStatus(status::SHADED);
        enemy.your_field[enemy.your_ships[index].x + enemy.your_ships[index].getSize()][crd.second].setStatus(status::SHADED);
        enemy.your_field[enemy.your_ships[index].x - 1][crd.second - 1].setStatus(status::SHADED);
        enemy.your_field[enemy.your_ships[index].x - 1][crd.second + 1].setStatus(status::SHADED);
        enemy.your_field[enemy.your_ships[index].x + enemy.your_ships[index].getSize()][crd.second - 1].setStatus(status::SHADED);
        enemy.your_field[enemy.your_ships[index].x + enemy.your_ships[index].getSize()][crd.second + 1].setStatus(status::SHADED);
        you.enemy_field[enemy.your_ships[index].x - 1][crd.second].setStatus(status::SHADED);
        you.enemy_field[enemy.your_ships[index].x + enemy.your_ships[index].getSize()][crd.second].setStatus(status::SHADED);
        you.enemy_field[enemy.your_ships[index].x - 1][crd.second - 1].setStatus(status::SHADED);
        you.enemy_field[enemy.your_ships[index].x - 1][crd.second + 1].setStatus(status::SHADED);
        you.enemy_field[enemy.your_ships[index].x + enemy.your_ships[index].getSize()][crd.second - 1].setStatus(status::SHADED);
        you.enemy_field[enemy.your_ships[index].x + enemy.your_ships[index].getSize()][crd.second + 1].setStatus(status::SHADED);
    }
    if(enemy.your_ships[index].direction == Ship::route::Y) {
        enemy.your_field[crd.first][enemy.your_ships[index].y - 1].setStatus(status::SHADED);
        enemy.your_field[crd.first][enemy.your_ships[index].y + enemy.your_ships[index].getSize()].setStatus(status::SHADED);
        enemy.your_field[crd.first - 1][enemy.your_ships[index].y - 1].setStatus(status::SHADED);
        enemy.your_field[crd.first + 1][enemy.your_ships[index].y - 1].setStatus(status::SHADED);
        enemy.your_field[crd.first - 1][enemy.your_ships[index].y + enemy.your_ships[index].getSize()].setStatus(status::SHADED);
        enemy.your_field[crd.first + 1][enemy.your_ships[index].y + enemy.your_ships[index].getSize()].setStatus(status::SHADED);
        you.enemy_field[crd.first][enemy.your_ships[index].y - 1].setStatus(status::SHADED);
        you.enemy_field[crd.first][enemy.your_ships[index].y + enemy.your_ships[index].getSize()].setStatus(status::SHADED);
        you.enemy_field[crd.first - 1][enemy.your_ships[index].y - 1].setStatus(status::SHADED);
        you.enemy_field[crd.first + 1][enemy.your_ships[index].y - 1].setStatus(status::SHADED);
        you.enemy_field[crd.first - 1][enemy.your_ships[index].y + enemy.your_ships[index].getSize()].setStatus(status::SHADED);
        you.enemy_field[crd.first + 1][enemy.your_ships[index].y + enemy.your_ships[index].getSize()].setStatus(status::SHADED);
    }
}
