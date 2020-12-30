#include <iostream>
#include <regex>
#include<string>
#include "GameView.h"
#include "Player.h"

const int size_of_field = 10;

int main() {
    Game game(size_of_field);
    game.GameInitial();
    game.GameFight();
    return 0;
}
