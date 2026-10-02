#pragma once

#include "Player.h"
#include "Position.h"
#include "Ship.h"

#include <string>
#include <stdexcept>

class Game {
public:
    Game();

    void start();

private:
    Player _user;
    Player _computer;

    void user_init(std::string input);
    void computer_init(std::string input);

    State user_move(std::string input);
    State computer_move();

    bool is_end();
    void show_game_window();

    int _diagStep;
    int _flatRow;
    int _flatCol;
};