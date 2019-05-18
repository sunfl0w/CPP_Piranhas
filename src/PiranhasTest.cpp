#include <chrono>
#include <iostream>

#include "PiranhasClient.hpp"
#include "GameState.hpp"
#include "PlayerColor.hpp"

using namespace std;
using namespace Piranhas;
using namespace Piranhas::Client;

void Bench1();
void Bench2();

int main() {
    cout << "Hello, World!\n";

    PiranhasClient piranhasClient;
    piranhasClient.Start("127.0.0.1", 13050);

    /*while (true) {
        Bench1();
        Bench2();
    }*/

    std::getchar();
    return 0;
}

void Bench1() {
    int searchCount = 0;
    GameState gameState = GameState(PlayerColor::Red);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < 1600) {
        std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
        searchCount++;
    }
    std::cout << "Searched moves " + std::to_string(searchCount) + " times in 1600ms\n";
}

void Bench2() {
    int searchCount = 0;
    GameState gameState = GameState(PlayerColor::Red);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < 1600) {
        int swarmSize = gameState.board.GetBiggestSwarmSize(Player(PlayerColor::Red));
        searchCount++;
    }
    std::cout << "Searched swarm " + std::to_string(searchCount) + " times in 1600ms\n";
}
