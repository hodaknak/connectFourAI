#include <iostream>

#include "GameState.h"

namespace cf {
    bool GameState::drop(const int col) {
        if (col < 0 || 7 <= col)
            return false;

        for (int i = 5; i >= 0; i--) {
            if (get(i, col) == Medal::EMPTY) {
                set(i, col, turn);
                toggle();

                return true;
            }
        }

        return false;
    }

    void GameState::display() const {
        std::cout << std::endl;

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                switch (get(i, j)) {
                    case Medal::EMPTY:
                        std::cout << " * ";
                        break;
                    case Medal::RED:
                        std::cout << " R ";
                        break;
                    case Medal::YELLOW:
                        std::cout << " Y ";
                        break;
                }
            }
            std::cout << std::endl;
        }

        std::cout << " 1  2  3  4  5  6  7 " << std::endl;

        std::cout << std::endl;
    }

    int GameState::winCheck() const {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (get(i, j) != Medal::EMPTY) {
                    bool win = false;

                    win += checkDirection(i, j, 0, 1, get(i, j));
                    win += checkDirection(i, j, -1, 1, get(i, j));
                    win += checkDirection(i, j, -1, 0, get(i, j));
                    win += checkDirection(i, j, -1, -1, get(i, j));
                    win += checkDirection(i, j, 0, -1, get(i, j));
                    win += checkDirection(i, j, 1, -1, get(i, j));
                    win += checkDirection(i, j, 1, 0, get(i, j));
                    win += checkDirection(i, j, 1, 1, get(i, j));

                    if (win) {
                        return static_cast<int>(get(i, j));
                    }
                }
            }
        }

        return 0;
    }

    std::array<Medal, 42> GameState::getBoard() const {
        return board;
    }


    Medal GameState::get(const int row, const int col) const {
        return board[row * 7 + col];
    }

    void GameState::set(const int row, const int col, const Medal value) {
        board[row * 7 + col] = value;
    }

    void GameState::toggle() {
        turn = turn == Medal::RED ? Medal::YELLOW : Medal::RED;
    }

    bool GameState::checkDirection(int centerRow, int centerCol, int dRow, int dCol, Medal color) const {
        int r = centerRow;
        int c = centerCol;

        for (int i = 0; i < 4; i++) {
            if (get(r, c) != color)
                return false;

            r += dRow;
            c += dCol;

            if (r >= 7 || c >= 7 || r < 0 || c < 0)
                return false;
        }

        return true;
    }
} // cf
