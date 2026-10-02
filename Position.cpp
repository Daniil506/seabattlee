#include "Position.h"

#include <cctype>
#include <cstdlib>
#include <sstream>

const int Position::_max_row = 10;
const int Position::_max_col = 10;

bool Position::is_collision(int row) {
    if (row < 1 || row > _max_row) {
        return true;
    }
    return false;
}

bool Position::is_collision(char col) {
    char c = toupper(col);
    if (c < 'A' || c > 'J') {
        return true;
    }
    return false;
}

Position::Position() {
    _row = rand() % _max_row + 1;
    _col = rand() % _max_col + 1;
}

Position::Position(int row, int col) {
    if (is_collision(row) || is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = col;
}

Position::Position(int row, char col) {
    if (is_collision(row) || is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = toupper(col) - 'A' + 1;
}

Position::Position(const Position& other) {
    _row = other._row;
    _col = other._col;
}

Position::Position(const std::string& str) {
    if (!parse(str, *this)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
}

int Position::row() const {
    return _row;
}

int Position::col() const {
    return _col;
}

char Position::char_col() const {
    return 'A' + _col - 1;
}

void Position::row(int value) {
    if (is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = value;
}

void Position::col(int value) {
    if (is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _col = value;
}

void Position::col(char value) {
    if (is_collision(value)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _col = toupper(value) - 'A' + 1;
}

bool parse(const std::string& str, Position& pos) {
    int i = 0;
    int n = (int)str.size();

    while (i < n && str[i] == ' ') {
        i++;
    }

    int start = i;
    while (i < n && isdigit(str[i])) {
        i++;
    }
    if (i == start) {
        return false;
    }
    int row = atoi(str.substr(start, i - start).c_str());

    while (i < n && str[i] == ' ') {
        i++;
    }
    if (i >= n) {
        return false;
    }

    char col = str[i];
    i++;

    while (i < n && str[i] == ' ') {
        i++;
    }
    if (i != n) {
        return false;
    }

    if (Position::is_collision(row) || Position::is_collision(col)) {
        return false;
    }

    pos._row = row;
    pos._col = toupper(col) - 'A' + 1;
    return true;
}

std::string to_string(const Position& pos) {
    std::ostringstream out;
    out << pos._row << pos.char_col();
    return out.str();
}