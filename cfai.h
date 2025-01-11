#ifndef CFAI_H
#define CFAI_H

#include <array>
#include <vector>

#include "GameState.h"

namespace cf {
    class cfai {
    public:
        explicit cfai(int depth, Medal color);

        int predict(const GameState &board) const;

    private:
        [[nodiscard]]
        static std::vector<int> generateMoves(const GameState &board);

        int minimax(const GameState &board, int depth, int alpha, int beta, bool maximizingPlayer) const;

        int eval(const GameState &board) const;

        int checkDirection(const GameState& board, int centerRow, int centerCol, int dRow, int dCol) const;

        const int depth;
        const Medal color;
    };
} // cf

#endif //CFAI_H
