#include "Game.h"

#include <iostream>
#include <sstream>

Game::Game() {
    _diagStep = 0;
    _flatRow = 0;
    _flatCol = 0;
}

void Game::user_init(std::string input) {
    std::istringstream stream(input);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.empty()) {
            continue;
        }
        try {
            Ship ship(line);
            _user.set_ship(ship);
        }
        catch (const std::logic_error&) {
            throw std::logic_error("Invalid input: incorrect field");
        }
    }

    if (!_user.check_ready()) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

void Game::computer_init(std::string input) {
    std::istringstream stream(input);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.empty()) {
            continue;
        }
        try {
            Ship ship(line);
            _computer.set_ship(ship);
        }
        catch (const std::logic_error&) {
            throw std::logic_error("Invalid input: incorrect field");
        }
    }

    if (!_computer.check_ready()) {
        throw std::logic_error("Invalid input: incorrect field");
    }
}

State Game::user_move(std::string input) {
    Position pos;
    if (!parse(input, pos)) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    try {
        return _computer.set_action(pos.row(), pos.char_col());
    }
    catch (const std::logic_error&) {
        throw std::logic_error("Invalid input: incorrect move");
    }
}

State Game::computer_move() {
    while (true) {
        int r = -1;
        int c = -1;

        if (_diagStep < 10) {
            r = _diagStep;
            c = _diagStep;
            _diagStep++;
        }
        else if (_diagStep < 20) {
            int k = _diagStep - 10;
            r = k;
            c = 9 - k;
            _diagStep++;
        }
        else {
            if (_flatRow >= 10) {
                throw std::logic_error("Invalid input: incorrect move");
            }
            r = _flatRow;
            c = _flatCol;
            _flatCol++;
            if (_flatCol >= 10) {
                _flatCol = 0;
                _flatRow++;
            }
        }

        char colChar = (char)('A' + c);
        try {
            return _user.set_action(r + 1, colChar);
        }
        catch (const std::logic_error&) {
            continue;
        }
    }
}

bool Game::is_end() {
    return _user.check_lose() || _computer.check_lose();
}

void Game::show_game_window() {
    std::cout << "= COMPUTER GAME FIELD =\n" << std::endl;
    _computer.show_field(true);

    std::cout << "\n=== YOUR PLAY FIELD ===\n" << std::endl;
    _user.show_field(false);
}

void Game::start() {
    std::string line;
    std::string userField;
    std::string compField;

    while (std::getline(std::cin, line) && !line.empty()) {
        userField += line + "\n";
    }

    while (std::getline(std::cin, line) && !line.empty()) {
        compField += line + "\n";
    }

    user_init(userField);
    computer_init(compField);

    while (!is_end()) {
        std::string move;
        if (!std::getline(std::cin, move)) {
            break;
        }
        if (move.empty()) {
            continue;
        }

        State userState;
        try {
            userState = user_move(move);
        }
        catch (const std::logic_error&) {
            continue;
        }

        while (userState == Hit && !is_end()) {
            if (!std::getline(std::cin, move)) {
                break;
            }
            if (move.empty()) {
                continue;
            }
            try {
                userState = user_move(move);
            }
            catch (const std::logic_error&) {
                break;
            }
        }

        if (is_end()) {
            break;
        }

        State compState = computer_move();
        while (compState == Hit && !is_end()) {
            compState = computer_move();
        }
    }

    show_game_window();

    if (_computer.check_lose()) {
        std::cout << "USER WIN!" << std::endl;
    }
    else {
        std::cout << "COMPUTER WIN!" << std::endl;
    }
}