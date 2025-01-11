#include "cfai.h"

#include <iostream>
#include <algorithm>
#include <future>

#define DEBUG_MODE

#define INFINITY 100000

namespace cf {
    cfai::cfai(const int depth, const Medal color) : depth{depth},
                                                     color{color} {
    }

    int cfai::predict(const GameState &board) const {
        const std::vector<int> moves = generateMoves(board);

        int highestVal = -INFINITY - 1;
        int output = 0;

        std::vector<int> moveCols;
        std::vector<std::future<int>> threads;

#ifdef DEBUG_MODE
        std::cout << '[' << std::flush;
#endif

        for (const auto move : moves) {
            GameState newBoard = board;
            newBoard.drop(move);

            moveCols.push_back(move);
            threads.emplace_back(std::async(std::launch::async, &cfai::minimax, this, newBoard, depth, -INFINITY, INFINITY, false));
        }

        for (int i = 0; i < threads.size(); i++) {
            const int val = threads[i].get();

#ifdef DEBUG_MODE
            std::cout << val << ", " << std::flush;
#endif

            if (highestVal < val) {
                highestVal = val;
                output = moveCols[i];
            }
        }

#ifdef DEBUG_MODE
        std::cout << ']' << std::endl;
#endif

        return output;
    }

    std::vector<int> cfai::generateMoves(const GameState &board) {
        std::vector<int> moves;

        for (int i = 0; i < 7; i++) {
            if (board.get(0, i) == Medal::EMPTY) {
                moves.push_back(i);
            }
        }

        return moves;
    }

    int cfai::minimax(const GameState &board, const int depth, int alpha, int beta, const bool maximizingPlayer) const {
        const auto moves = generateMoves(board);

        if (const int winner = board.winCheck()) {
            if (winner == static_cast<int>(color))
                return INFINITY;
            return -INFINITY;
        }

        if (depth == 0 || moves.empty()) {
            return eval(board);
        }

        if (maximizingPlayer) {
            int value = -INFINITY;

            for (const int move : moves) {
                GameState newBoard = board;
                newBoard.drop(move);

                value = std::max(value, minimax(newBoard, depth - 1, alpha, beta, false));
                alpha = std::max(alpha, value);
                if (value >= beta)
                    break;
            }

            return value;
        } else {
            int value = INFINITY;

            for (const int move : moves) {
                GameState newBoard = board;
                newBoard.drop(move);

                value = std::min(value, minimax(newBoard, depth - 1, alpha, beta, true));
                beta = std::min(beta, value);
                if (value <= alpha)
                    break;
            }

            return value;
        }
    }

    int cfai::eval(const GameState &board) const {
        // center column
        int score = 0;

        for (int i = 0; i < 6; i++) {
            if (board.get(i, 3) != Medal::EMPTY) {
                if (board.get(i, 3) == color) {
                    score += 5;
                } else {
                    score -= 5;
                }
            }
        }

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (board.get(i, j) != Medal::EMPTY) {
                    score += checkDirection(board, i, j, 0, 1);
                    score += checkDirection(board, i, j, -1, 1);
                    score += checkDirection(board, i, j, -1, 0);
                    score += checkDirection(board, i, j, -1, -1);
                    score += checkDirection(board, i, j, 0, -1);
                    score += checkDirection(board, i, j, 1, -1);
                    score += checkDirection(board, i, j, 1, 0);
                    score += checkDirection(board, i, j, 1, 1);
                }
            }
        }

        if (score > INFINITY)
            return INFINITY;
        if (score < -INFINITY)
            return -INFINITY;

        return score;
    }

    int cfai::checkDirection(const GameState& board, const int centerRow, const int centerCol, const int dRow, const int dCol) const {
        const Medal col = board.get(centerRow, centerCol);

        int count = 0;
        int r = centerRow;
        int c = centerCol;

        for (int i = 0; i < 4; i++) {
            if (board.get(r, c) == col)
                count++;
            else
                break;

            r += dRow;
            c += dCol;
        }

        int score;

        switch (count) {
            case 2:
                score = 3;
                break;
            case 3:
                score = 25;
                break;
            case 4:
                score = INFINITY;
                break;
            default:
                score = 0;
        }

        if (col == color)
            return score;

        return -score;
    }

} // cf
