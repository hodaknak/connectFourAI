#include <iostream>
#include <limits>

#include "cfai.h"
#include "GameState.h"

int main() {
    auto g = cf::GameState();
    const auto ai = cf::cfai(9, cf::Medal::YELLOW);

    while (true) {
        std::cout << "Enter a move: ";

        int row;
        std::cin >> row;
        row -= 1;

        if (row == -1)
            break;

        if (!g.drop(row))
            continue;

        if (const int winner = g.winCheck(); winner == static_cast<int>(cf::Medal::RED)) {
            std::cout << "Red wins!" << std::endl;
            break;
        } else if (winner == static_cast<int>(cf::Medal::YELLOW)) {
            std::cout << "Yellow wins!" << std::endl;
            break;
        }

        g.display();

        const int aiMove = ai.predict(g);
        std::cout << "AI move: " << aiMove + 1 << std::endl;

        if (!g.drop(aiMove)) {
            std::cerr << "AI Error" << std::endl;
            return 1;
        }

        g.display();

        if (const int winner = g.winCheck(); winner == static_cast<int>(cf::Medal::RED)) {
            std::cout << "Red wins!" << std::endl;
            break;
        } else if (winner == static_cast<int>(cf::Medal::YELLOW)) {
            std::cout << "Yellow wins!" << std::endl;
            break;
        }

        std::cout << std::endl;
    }

    return 0;
}