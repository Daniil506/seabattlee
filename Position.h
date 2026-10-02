#pragma once

#include <string>
#include <stdexcept>

class Position {
public:
    Position();
    Position(int row, int col);
    Position(int row, char col);
    Position(const Position& other);
    Position(const std::string& str);

    int row() const;
    int col() const;
    char char_col() const;

    void row(int value);
    void col(int value);
    void col(char value);

    static bool is_collision(int row);
    static bool is_collision(char col);

    friend bool parse(const std::string& str, Position& pos);
    friend std::string to_string(const Position& pos);

private:
    int _row;
    int _col;

    static const int _max_row;
    static const int _max_col;
};