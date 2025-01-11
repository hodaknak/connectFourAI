#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <array>

namespace cf {
    enum class Medal {
        EMPTY,
        RED,
        YELLOW
    };

    class GameState {
    public:
        bool drop(int col);

        void display() const;

        [[nodiscard]]
        int winCheck() const;

        [[nodiscard]]
        std::array<Medal, 42> getBoard() const;

        [[nodiscard]]
        Medal get(int row, int col) const;

        void set(int row, int col, Medal value);

    private:
        void toggle();

        [[nodiscard]]
        bool checkDirection(int centerRow, int centerCol, int dRow, int dCol, Medal color) const;

        Medal turn = Medal::RED;
        std::array<Medal, 42> board = {Medal::EMPTY};
    };
} // cf

#endif //GAMESTATE_H
