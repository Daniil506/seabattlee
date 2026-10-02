#pragma once

#include "GameField.h"
#include "Ship.h"
#include "Position.h"

#include <string>
#include <stdexcept>

class Player {
public:
    Player();

    void set_ship(const Ship& ship);
    State set_action(int row, char col);
    void show_field(bool hide_ships = false);
    bool check_lose();
    bool check_ready();

private:
    GameField _gamefield;
    int _ships_counts[4];

    static const int _max_ships_counts[4];
};