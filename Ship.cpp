#include "Ship.h"

#include <cctype>
#include <sstream>

bool Ship::is_collision(int size, Position position, Direction direction) {
    if (size < 1 || size > 4) {
        return true;
    }

    int row = position.row();
    int col = position.col();

    if (direction == Horizontal) {
        if (col + size - 1 > 10) {
            return true;
        }
    }
    else {
        if (row + size - 1 > 10) {
            return true;
        }
    }

    return false;
}

Ship::Ship(int size, const Position& position, Direction direction) {
    if (is_collision(size, position, direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = size;
    _position = position;
    _direction = direction;
}

Ship::Ship(int size, char direction, int row, char col) {
    Position pos(row, col);

    Direction dir;
    char d = toupper(direction);
    if (d == 'H') {
        dir = Horizontal;
    }
    else if (d == 'V') {
        dir = Vertical;
    }
    else {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    if (is_collision(size, pos, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    _size = size;
    _position = pos;
    _direction = dir;
}

Ship::Ship(const std::string& str) {
    if (!parse(str, *this)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

int Ship::size() const {
    return _size;
}

int Ship::row() const {
    return _position.row();
}

int Ship::col() const {
    return _position.col();
}

Position Ship::position() const {
    return _position;
}

Direction Ship::direction() const {
    return _direction;
}

void Ship::size(int value) {
    if (is_collision(value, _position, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = value;
}

void Ship::row(int value) {
    Position newPos(value, _position.col());
    if (is_collision(_size, newPos, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = newPos;
}

void Ship::col(int value) {
    Position newPos(_position.row(), value);
    if (is_collision(_size, newPos, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = newPos;
}

void Ship::col(char value) {
    Position newPos(_position.row(), value);
    if (is_collision(_size, newPos, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = newPos;
}

void Ship::direction(Direction value) {
    if (is_collision(_size, _position, value)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = value;
}

void Ship::direction(char value) {
    Direction dir;
    char d = toupper(value);
    if (d == 'H') {
        dir = Horizontal;
    }
    else if (d == 'V') {
        dir = Vertical;
    }
    else {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    if (is_collision(_size, _position, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = dir;
}

void Ship::position(const Position& value) {
    if (is_collision(_size, value, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = value;
}

bool parse(const std::string& str, Ship& ship) {
    int i = 0;
    int n = (int)str.size();

    while (i < n && str[i] == ' ') i++;
    int start = i;
    while (i < n && isdigit(str[i])) i++;
    if (i == start) return false;
    int size = atoi(str.substr(start, i - start).c_str());

    while (i < n && str[i] == ' ') i++;
    if (i >= n) return false;

    char dirChar = str[i];
    i++;

    while (i < n && str[i] == ' ') i++;
    if (i >= n) return false;

    std::string posStr = str.substr(i);
    Position pos;
    if (!parse(posStr, pos)) {
        return false;
    }

    Direction dir;
    char d = toupper(dirChar);
    if (d == 'H') {
        dir = Horizontal;
    }
    else if (d == 'V') {
        dir = Vertical;
    }
    else {
        return false;
    }

    if (Ship::is_collision(size, pos, dir)) {
        return false;
    }

    ship._size = size;
    ship._position = pos;
    ship._direction = dir;
    return true;
}

std::string to_string(const Ship& ship) {
    std::ostringstream out;
    out << ship._size << ' ';
    if (ship._direction == Horizontal) {
        out << 'H';
    }
    else {
        out << 'V';
    }
    out << ' ' << to_string(ship._position);
    return out.str();
}