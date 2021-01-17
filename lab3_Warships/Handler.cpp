#include "Handler.h"

bool Handler::step(Player &you, Player &enemy) {
    bool shoot_is_successful = false;

    std::pair<int, int> crd = you.shoot();
    while(crd.first == -1 || crd.second == -1 || you.getEnemyCell(crd.first, crd.second) == status::DAMAGE ||
                                                  you.getEnemyCell(crd.first, crd.second) == status::SHADED) {
        crd = you.shoot();
    }

    for(int i = 0; i < enemy.getCountOfShips(); ++i){
        if(enemy.getShip(i).damage(crd.first, crd.second)) {
            //устанавливаем статус ячейки у противника и союзника
            enemy.setFriendCell(crd.first, crd.second, status::DAMAGE);
            you.setEnemyCell(crd.first, crd.second, status::DAMAGE);
            shoot_is_successful = true;
            //Если корабль уничтожен, то сбрасываем статус последнего выстрела для HardBot, для всех
            //остальных закрашиваем клетки вокруг этого корабля, в том числе и для HardBot
            std::cout << enemy.getShip(i).getHealth() << std::endl;
            if(enemy.getShip(i).getHealth() == 0) {
                Destroy_ship(you, enemy, i);
            }
        }
    }

    if(!shoot_is_successful) {
        enemy.setFriendCell(crd.first, crd.second, status::SHADED);
        you.setEnemyCell(crd.first, crd.second, status::SHADED);
    }

    return shoot_is_successful;
}

Handler::Handler(Player &plr1, Player &plr2) : plr1(plr1), plr2(plr2) {}

void Handler::Destroy_ship(Player &you, Player &enemy, int index) {
    Ship ship = enemy.getShip(index);
    if(ship.direction == Ship::route::X) {
        if(ship.x > 0) {
            you.setEnemyCell(ship.x - 1, ship.y, status::SHADED);
            enemy.setFriendCell(ship.x - 1, ship.y, status::SHADED);
            if(ship.y > 0) {
                you.setEnemyCell(ship.x - 1, ship.y - 1, status::SHADED);
                enemy.setFriendCell(ship.x - 1, ship.y - 1, status::SHADED);
            }
            if(ship.y < 9) {
                you.setEnemyCell(ship.x - 1, ship.y + 1, status::SHADED);
                enemy.setFriendCell(ship.x - 1, ship.y + 1, status::SHADED);
            }
        }
        for (int i = 0; i < ship.getSize(); ++i) {
            if(ship.where()[i].second > 0) {
                you.setEnemyCell(ship.where()[i].first, ship.where()[i].second - 1, status::SHADED);
                enemy.setFriendCell(ship.where()[i].first, ship.where()[i].second - 1, status::SHADED);
            }
            if(ship.where()[i].second < 9) {
                you.setEnemyCell(ship.where()[i].first, ship.where()[i].second + 1, status::SHADED);
                enemy.setFriendCell(ship.where()[i].first, ship.where()[i].second + 1, status::SHADED);
            }
        }
        if(ship.x + ship.getSize() - 1 < 9) {
            you.setEnemyCell(ship.x + ship.getSize(), ship.y, status::SHADED);
            enemy.setFriendCell(ship.x + ship.getSize(), ship.y, status::SHADED);
            if(ship.y > 0) {
                you.setEnemyCell(ship.x + ship.getSize(), ship.y - 1, status::SHADED);
                enemy.setFriendCell(ship.x + ship.getSize(), ship.y - 1, status::SHADED);
            }
            if(ship.y < 9) {
                you.setEnemyCell(ship.x + ship.getSize(), ship.y + 1, status::SHADED);
                enemy.setFriendCell(ship.x + ship.getSize(), ship.y + 1, status::SHADED);
            }
        }
    }
    if(ship.direction == Ship::route::Y) {
        if(ship.y > 0) {
            you.setEnemyCell(ship.x, ship.y - 1, status::SHADED);
            enemy.setFriendCell(ship.x, ship.y - 1, status::SHADED);
            if(ship.x > 0) {
                you.setEnemyCell(ship.x - 1, ship.y - 1, status::SHADED);
                enemy.setFriendCell(ship.x - 1, ship.y - 1, status::SHADED);
            }
            if(ship.x < 9) {
                you.setEnemyCell(ship.x + 1, ship.y - 1, status::SHADED);
                enemy.setFriendCell(ship.x + 1, ship.y - 1, status::SHADED);
            }
        }
        for (int i = 0; i < ship.getSize(); ++i) {
            if(ship.where()[i].first > 0) {
                you.setEnemyCell(ship.where()[i].first - 1, ship.where()[i].second, status::SHADED);
                enemy.setFriendCell(ship.where()[i].first - 1, ship.where()[i].second, status::SHADED);
            }
            if(ship.where()[i].first < 9) {
                you.setEnemyCell(ship.where()[i].first + 1, ship.where()[i].second, status::SHADED);
                enemy.setFriendCell(ship.where()[i].first + 1, ship.where()[i].second, status::SHADED);
            }
        }
        if(ship.y + ship.getSize() - 1 < 9) {
            you.setEnemyCell(ship.x, ship.y + ship.getSize(), status::SHADED);
            enemy.setFriendCell(ship.x, ship.y + ship.getSize(), status::SHADED);
            if(ship.x > 0) {
                you.setEnemyCell(ship.x - 1, ship.y + ship.getSize(), status::SHADED);
                enemy.setFriendCell(ship.x - 1, ship.y + ship.getSize(), status::SHADED);
            }
            if(ship.x < 9) {

                you.setEnemyCell(ship.x + 1, ship.y + ship.getSize(), status::SHADED);
                enemy.setFriendCell(ship.x + 1, ship.y + ship.getSize(), status::SHADED);
            }
        }
    }
}
