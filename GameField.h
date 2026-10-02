#pragma once

#include "Ship.h"
#include "Position.h"

#include <string>
#include <stdexcept>

enum State { Missed, BoatDestroyed, DestroyersDestroyed, CruisersDestroyed, BattleshipDestroyed, Hit };

class GameField {
public:
    GameField();
    ~GameField();

    void set(const Ship& ship);
    State set(int row, char col);

    friend std::string to_string(const GameField& field, bool showShips);
    friend bool is_collision(const GameField& field, const Ship& ship);

private:
    char** _field;
    const int _n;
    const int _m;

    int check_destroy(int row, int col);
};