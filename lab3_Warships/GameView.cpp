#include "GameView.h"

Game::Game(size_t size_of_field) :size_of_field(size_of_field) {
    std::cout << "Please write type of Player1 (1-Human; 2-hardBot; 3-easyBot)" << std::endl;
    int typeplr1, typeplr2;
    std::cin >> typeplr1;
    std::cout << std::endl << "Please write type of Player2 (1-Human; 2-hardBot; 3-easyBot)" << std::endl;
    std::cin >> typeplr2;
    if(typeplr1 == 1) {
        plr1 = std::make_unique<Human>(count_of_ship);
    }
    if(typeplr2 == 1) {
        plr2 = std::make_unique<Human>(count_of_ship);
    }
    if(typeplr1 == 2) {
        plr1 = std::make_unique<HardBot>(count_of_ship);
    }
    if(typeplr1 == 3) {
        plr1 = std::make_unique<EasyBot>(count_of_ship);
    }
    if(typeplr2 == 2) {
        plr2 = std::make_unique<HardBot>(count_of_ship);
    }
    if(typeplr2 == 3) {
        plr2 = std::make_unique<EasyBot>(count_of_ship);
    }

    plr1_enemy_field.resize(size_of_field);
    plr2_enemy_field.resize(size_of_field);
    plr1_friend_field.resize(size_of_field);
    plr2_friend_field.resize(size_of_field);

    for(int i = 0; i < size_of_field; ++i) {

        plr1_enemy_field[i].resize(size_of_field);
        plr2_enemy_field[i].resize(size_of_field);
        plr1_friend_field[i].resize(size_of_field);
        plr2_friend_field[i].resize(size_of_field);

        for(int j = 0; j < size_of_field; ++j) {
            plr1_enemy_field[i][j] = 'o';
            plr2_enemy_field[i][j] = 'o';
            plr1_friend_field[i][j] = 'o';
            plr2_friend_field[i][j] = 'o';
        }
    }
}

void Game::GameInitial() {
    DrawView(1);
    for(int i = 0; i < count_of_big; ++i) {
        if(plr1->name != "easy_bot" && plr1->name != "hard_bot"){
            std::cout << "please choose position for 4-ship" << std::endl;
        }
        bool complete_plr1 = plr1->place_ship(4);
        while(!complete_plr1) {
            std::cout << "please choose position for 4-ship" << std::endl;
            complete_plr1 = plr1->place_ship(4);
        }
        RestoreInfo();
        DrawView(1);
    }
    for(int i = 0; i < count_of_medium_big; ++i) {
        if(plr1->name != "easy_bot" && plr1->name != "hard_bot"){
            std::cout << "please choose position for 3-ship" << std::endl;
        }
        bool complete_plr1 = plr1->place_ship(3);
        while(!complete_plr1) {
            complete_plr1 = plr1->place_ship(3);
        }
        RestoreInfo();
        DrawView(1);
    }
    for(int i = 0; i < count_of_medium_small; ++i) {
        if(plr1->name != "easy_bot" && plr1->name != "hard_bot"){
            std::cout << "please choose position for 2-ship" << std::endl;
        }
        bool complete_plr1 = plr1->place_ship(2);
        while(!complete_plr1) {
            complete_plr1 = plr1->place_ship(2);
        }
        RestoreInfo();
        DrawView(1);
    }
    for(int i = 0; i < count_of_small; ++i){
        if(plr1->name != "easy_bot" && plr1->name != "hard_bot"){
            std::cout << "please choose position for 1-ship" << std::endl;
        }
        bool complete_plr1 = plr1->place_ship(1);
        while(!complete_plr1) {
            complete_plr1 = plr1->place_ship(1);
        }
        RestoreInfo();
        DrawView(1);
    }

    for(int i = 0; i < count_of_big; ++i) {
        if(plr2->name != "easy_bot" && plr2->name != "hard_bot"){
            std::cout << "please choose position for 4-ship" << std::endl;
        }
        bool complete_plr2 = plr2->place_ship(4);
        while(!complete_plr2) {
            complete_plr2 = plr2->place_ship(4);
        }
        RestoreInfo();
        DrawView(2);
    }
    for(int i = 0; i < count_of_medium_big; ++i) {
        if(plr2->name != "easy_bot" && plr2->name != "hard_bot"){
            std::cout << "please choose position for 3-ship" << std::endl;
        }
        bool complete_plr2 = plr2->place_ship(3);
        while(!complete_plr2) {
            complete_plr2 = plr2->place_ship(3);
        }
        RestoreInfo();
        DrawView(2);
    }
    for(int i = 0; i < count_of_medium_small; ++i) {
        if(plr2->name != "easy_bot" && plr2->name != "hard_bot"){
            std::cout << "please choose position for 2-ship" << std::endl;
        }
        bool complete_plr2 = plr2->place_ship(2);
        while(!complete_plr2) {
            complete_plr2 = plr2->place_ship(2);
        }
        RestoreInfo();
        DrawView(2);
    }
    for(int i = 0; i < count_of_small; ++i){
        if(plr2->name != "easy_bot" && plr2->name != "hard_bot"){
            std::cout << "please choose position for 1-ship" << std::endl;
        }
        bool complete_plr2 = plr2->place_ship(1);
        while(!complete_plr2) {
            complete_plr2 = plr2->place_ship(1);
        }
        RestoreInfo();
        DrawView(2);
    }
}

void Game::GameFight() {
    Handler hand(*plr1, *plr2);
    while(true) {
        std::cout << "Player1 - your turn to shoot, chose cell x y :" << std::endl;
        while(hand.step(hand.plr1, hand.plr2)) {
            RestoreInfo();
            std::cout << "success, try again!" << std::endl;
            DrawView(1);
            size_t health = 0;
            for(auto x : plr2->your_ships) {
                health += x.getHealth();
            }
            if(health == 0) {
                std::cout << "Player1 Win!!!" << std::endl;
                return;
            }
        }
        std::cout << "Player2 - your turn to shoot, chose cell x y :" << std::endl;
        while(hand.step(hand.plr2, hand.plr1)) {
            RestoreInfo();
            std::cout << "success, try again!" << std::endl;
            DrawView(2);
            size_t health = 0;
            for(auto x : plr1->your_ships) {
                health += x.getHealth();
            }
            if(health == 0) {
                std::cout << "Player2 Win!!!" << std::endl;
                return;
            }
        }
    }
}

void Game::DrawView(size_t number) {
    std::cout << "   your field     enemy field" << std::endl;
    std::cout << "   ABCDEFGHIJ     ABCDEFGHIJ" << std::endl;
    for(int i = 0; i < size_of_field; ++i) {
        std::cout << i + 1 << ' ';
        if(i != 9) {
            std::cout << ' ';
        }
        for(int j = 0; j < size_of_field; ++j) {
            if(number == 1) {
                std::cout << plr1_friend_field[i][j];
            }
            else {
                std::cout << plr2_friend_field[i][j];
            }
        }
        std::cout << "  " ;
        std::cout << i + 1 << ' ';
        if(i != 9) {
            std::cout << ' ';
        }
        for(int j = 0; j < size_of_field; ++j) {
            if(number == 1) {
                std::cout << plr1_enemy_field[i][j];
            }
            else {
                std::cout << plr2_enemy_field[i][j];
            }
        }
        std::cout << std::endl;
    }
}

// o = CLEAR, x = DAMAGE, w = SHADED, T = SHIP

void Game::RestoreInfo() {
    for(int i = 0; i < size_of_field; ++i) {
        for(int j = 0; j < size_of_field; ++j) {
            if(plr1->your_field[i][j].getStatus() == status::SHADED) {
                plr1_friend_field[i][j] = 'w';
                plr2_enemy_field[i][j] = 'w';
            }
            if(plr1->your_field[i][j].getStatus() == status::DAMAGE) {
                plr1_friend_field[i][j] = 'X';
                plr2_enemy_field[i][j] = 'X';
            }
            if(plr1->your_field[i][j].getStatus() == status::SHIP) {
                plr1_friend_field[i][j] = 'T';
            }
            if(plr2->your_field[i][j].getStatus() == status::SHADED) {
                plr2_friend_field[i][j] = 'w';
                plr1_enemy_field[i][j] = 'w';
            }
            if(plr2->your_field[i][j].getStatus() == status::DAMAGE) {
                plr2_friend_field[i][j] = 'X';
                plr1_enemy_field[i][j] = 'X';
            }
            if(plr2->your_field[i][j].getStatus() == status::SHIP) {
                plr2_friend_field[i][j] = 'T';
            }
        }
    }
}



