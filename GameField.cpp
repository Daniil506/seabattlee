#include "GameField.h"

#include <cctype>
#include <sstream>

GameField::GameField() : _n(10), _m(10) {
    _field = new char* [_n];
    for (int i = 0; i < _n; i++) {
        _field[i] = new char[_m];
        for (int j = 0; j < _m; j++) {
            _field[i][j] = ' ';
        }
    }
}

GameField::~GameField() {
    for (int i = 0; i < _n; i++) {
        delete[] _field[i];
    }
    delete[] _field;
}

void GameField::set(const Ship& ship) {
    if (is_collision(*this, ship)) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    int row = ship.row() - 1;
    int col = ship.col() - 1;

    for (int k = 0; k < ship.size(); k++) {
        if (ship.direction() == Horizontal) {
            _field[row][col + k] = '*';
        }
        else {
            _field[row + k][col] = '*';
        }
    }
}

State GameField::set(int row, char col) {
    if (row < 1 || row > _n) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    char c = toupper(col);
    if (c < 'A' || c >= 'A' + _m) {
        throw std::logic_error("Invalid input: incorrect move");
    }

    int r = row - 1;
    int cc = c - 'A';

    if (_field[r][cc] == '.' || _field[r][cc] == 'X') {
        throw std::logic_error("Invalid input: incorrect move");
    }

    if (_field[r][cc] == '*') {
        _field[r][cc] = 'X';

        int destroyed = check_destroy(r, cc);
        if (destroyed == 0) {
            return Hit;
        }
        if (destroyed == 1) {
            return BoatDestroyed;
        }
        if (destroyed == 2) {
            return DestroyersDestroyed;
        }
        if (destroyed == 3) {
            return CruisersDestroyed;
        }
        return BattleshipDestroyed;
    }

    _field[r][cc] = '.';
    return Missed;
}

int GameField::check_destroy(int row, int col) {
    int minRow = row;
    int maxRow = row;
    int minCol = col;
    int maxCol = col;

    while (minRow - 1 >= 0 && (_field[minRow - 1][col] == '*' || _field[minRow - 1][col] == 'X')) {
        minRow--;
    }
    while (maxRow + 1 < _n && (_field[maxRow + 1][col] == '*' || _field[maxRow + 1][col] == 'X')) {
        maxRow++;
    }
    while (minCol - 1 >= 0 && (_field[row][minCol - 1] == '*' || _field[row][minCol - 1] == 'X')) {
        minCol--;
    }
    while (maxCol + 1 < _m && (_field[row][maxCol + 1] == '*' || _field[row][maxCol + 1] == 'X')) {
        maxCol++;
    }

    if (minRow != maxRow) {
        for (int r = minRow; r <= maxRow; r++) {
            if (_field[r][col] != 'X') {
                return 0;
            }
        }
        return maxRow - minRow + 1;
    }

    if (minCol != maxCol) {
        for (int c = minCol; c <= maxCol; c++) {
            if (_field[row][c] != 'X') {
                return 0;
            }
        }
        return maxCol - minCol + 1;
    }

    return 1;
}

bool is_collision(const GameField& field, const Ship& ship) {
    int row = ship.row() - 1;
    int col = ship.col() - 1;
    int size = ship.size();

    for (int k = 0; k < size; k++) {
        int r = row;
        int c = col;

        if (ship.direction() == Horizontal) {
            c = col + k;
        }
        else {
            r = row + k;
        }

        if (r < 0 || r >= field._n || c < 0 || c >= field._m) {
            return true;
        }

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int nr = r + dr;
                int nc = c + dc;
                if (nr < 0 || nr >= field._n || nc < 0 || nc >= field._m) {
                    continue;
                }
                if (field._field[nr][nc] != ' ') {
                    return true;
                }
            }
        }
    }

    return false;
}

std::string to_string(const GameField& field, bool showShips) {
    std::ostringstream out;

    out << "  |";
    for (int j = 0; j < field._m; j++) {
        out << (char)('A' + j);
        if (j < field._m - 1) {
            out << ' ';
        }
    }
    out << "|\n";

    out << "  +";
    for (int j = 0; j < field._m; j++) {
        out << '-';
        if (j < field._m - 1) {
            out << '-';
        }
    }
    out << "-+\n";

    for (int i = 0; i < field._n; i++) {
        out << (i + 1) << " |";
        for (int j = 0; j < field._m; j++) {
            char cell = field._field[i][j];
            if (cell == '*' && !showShips) {
                cell = ' ';
            }
            out << cell << '|';
        }
        out << "\n";
    }

    out << "  +";
    for (int j = 0; j < field._m; j++) {
        out << '-';
        if (j < field._m - 1) {
            out << '-';
        }
    }
    out << "-+\n";

    return out.str();
}