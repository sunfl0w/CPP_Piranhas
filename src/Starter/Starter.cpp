#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <iostream>

#include "Piranhas/GameState.hpp"
#include "Client/PiranhasClient.hpp"
#include "Piranhas/PlayerColor.hpp"

using namespace std;
using namespace Piranhas;
using namespace Client;
using namespace AI::Evaluation;
using namespace boost::program_options;

void Bench1();
void Bench2();
void Bench3();
void Bench4();
void Bench5();
void Test();

int main(int argc, char *argv[]) {
    cout << "Hello, World! I am a c++ client!\n";
    cout << "Parsing arguments.\n";

    options_description optionsDesribtion("C++ client");
    optionsDesribtion.add_options()("host,h", value<std::string>()->default_value("localhost"), "Host")("port,p", value<unsigned short>()->default_value(13050), "Port")("reservation,r", value<std::string>()->default_value(""), "ReservationCode");

    variables_map varibaleMap;
    store(command_line_parser(argc, argv).options(optionsDesribtion).run(), varibaleMap);

    std::string hostname = "localhost";
    unsigned short hostPort = 13050;
    std::string reservationCode;

    if (varibaleMap.count("host")) {
        hostname = varibaleMap["host"].as<std::string>();
    }
    if (varibaleMap.count("port")) {
        hostPort = varibaleMap["port"].as<unsigned short>();
    }
    if (varibaleMap.count("reservation")) {
        reservationCode = varibaleMap["reservation"].as<std::string>();
    }

    std::cout << "Parsing complete. Arguments are:\n";
    std::cout << "HostName: " + hostname + "\n";
    std::cout << "HostPort: " + std::to_string(hostPort) + "\n";
    std::cout << "ReservationCode: " + reservationCode + "\n";

    io_service ioService;
    PiranhasClient piranhasClient(ioService);

    if (reservationCode.size() == 0) {
        std::cout << "Start.\n";
        piranhasClient.Start(ip::address::from_string("127.0.0.1"), hostPort);
    } else {
        std::cout << "Start reserved.\n";
        piranhasClient.StartReserved(hostname, hostPort, reservationCode);
    }

    /*while (true) {
        Bench1();
        Bench2();
        Bench3();
        Bench4();
        Bench5();
    }*/
    //Test();
    //std::getchar();ZZ

    return 0;
}

void Bench1() {
    int searchCount = 0;
    GameState gameState = GameState(PlayerColor::Red);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < 1600) {
        std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
        //std::cout << "Size: " << possibleMoves.size() << "\n";
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

void Bench3() {
    int count = 0;
    Move move = Move(Position(0, 1), Direction::Up);
    GameState gameState = GameState(PlayerColor::Red);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < 1600) {
        GameState clonedGameState = GameState(gameState);
        clonedGameState.PerformMove(move);
        count++;
    }
    std::cout << "Cloned GS and performed move " + std::to_string(count) + " times in 1600ms\n";
}

void Bench4() {
    int count = 0;
    Move move = Move(Position(0, 1), Direction::Up);
    GameState gameState = GameState(PlayerColor::Red);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < 1600) {
        gameState.PerformMove(move);
        gameState.RevertLastPerformedMove();
        count++;
    }
    std::cout << "Performed move and reverted it " + std::to_string(count) + " times in 1600ms\n";
}

void Bench5() {
    int count = 0;
    GameState gameState = GameState(PlayerColor::Red);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < 1600) {
        std::vector<Field> checkers = gameState.board.GetAllFieldsOfSameType(FieldType::Red);
        int swarmSize = gameState.board.GetBiggestSwarmSizeTest(checkers);
        //std::cout << "Size: " << swarmSize << "\n";
        count++;
    }
    std::cout << "Searched swarm " + std::to_string(count) + " times in 1600ms\n";
}

void Test() {
    Move move = Move(Position(0, 1), Direction::Up);
    GameState gameState = GameState(PlayerColor::Red);

    GameState clonedGameState = GameState(gameState);
    clonedGameState.PerformMove(move);
    clonedGameState.board.Print();

    float eval = Evaluator::EvaluateGameState(clonedGameState);

    float x = 0.0f;
    std::cout << "Score: " << std::to_string(eval) << "\n";
}
