#pragma once

#include "Position.h"

#include <string>
#include <stdexcept>

enum Direction { Horizontal, Vertical };

class Ship {
public:
    Ship(int size, const Position& position, Direction direction);
    Ship(int size, char direction, int row, char col);
    Ship(const std::string& str);

    int size() const;
    int row() const;
    int col() const;
    Position position() const;
    Direction direction() const;

    void size(int value);
    void row(int value);
    void col(int value);
    void col(char value);
    void direction(Direction value);
    void direction(char value);
    void position(const Position& value);

    static bool is_collision(int size, Position position, Direction direction);

    friend bool parse(const std::string& str, Ship& ship);
    friend std::string to_string(const Ship& ship);

private:
    int _size;
    Position _position;
    Direction _direction;
};