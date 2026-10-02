#include "Player.h"

#include <iostream>

const int Player::_max_ships_counts[4] = { 4, 3, 2, 1 };

Player::Player() {
    for (int i = 0; i < 4; i++) {
        _ships_counts[i] = 0;
    }
}

void Player::set_ship(const Ship& ship) {
    int idx = ship.size() - 1;
    if (idx < 0 || idx > 3) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    if (_ships_counts[idx] >= _max_ships_counts[idx]) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    try {
        _gamefield.set(ship);
    }
    catch (const std::logic_error&) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    _ships_counts[idx]++;
}

State Player::set_action(int row, char col) {
    try {
        return _gamefield.set(row, col);
    }
    catch (const std::logic_error&) {
        throw std::logic_error("Invalid input: incorrect move");
    }
}

void Player::show_field(bool hide_ships) {
    std::cout << to_string(_gamefield, !hide_ships);

    std::cout << "\nShips Left:\n";
    std::cout << "* - " << (_max_ships_counts[0] - _ships_counts[0]);
    std::cout << " ** - " << (_max_ships_counts[1] - _ships_counts[1]);
    std::cout << " *** - " << (_max_ships_counts[2] - _ships_counts[2]);
    std::cout << " **** - " << (_max_ships_counts[3] - _ships_counts[3]);
    std::cout << std::endl;
}

bool Player::check_lose() {
    for (int i = 0; i < 4; i++) {
        if (_ships_counts[i] > 0) {
            return false;
        }
    }
    return true;
}

bool Player::check_ready() {
    for (int i = 0; i < 4; i++) {
        if (_ships_counts[i] != _max_ships_counts[i]) {
            return false;
        }
    }
    return true;
}