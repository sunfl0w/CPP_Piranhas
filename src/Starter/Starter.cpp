#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>

#include "GameState.hpp"
#include "PiranhasClient.hpp"
#include "PlayerColor.hpp"

using namespace std;
using namespace Piranhas;
using namespace Piranhas::Client;
using namespace boost::program_options;

void Bench1();
void Bench2();

int main(int argc, char *argv[]) {
    cout << "Hello, World! I am a c++ client!\n";
    cout << "Parsing argument.\n";

    options_description optionsDesribtion("C++ client");
    optionsDesribtion.add_options()("host,h", value<std::string>()->default_value("localhost"), "Host")("port,p", value<unsigned short>()->default_value(13050), "Port")("reservation,r", value<std::string>()->default_value(""), "ReservationCode");

    variables_map varibaleMap;
    store(command_line_parser(argc, argv).options(optionsDesribtion).run(), varibaleMap);

    std::string hostName;
    unsigned short hostPort;
    std::string reservationCode;

    if (varibaleMap.count("host")) {
        hostName = varibaleMap["host"].as<std::string>();
    }
    if (varibaleMap.count("port")) {
        hostPort = varibaleMap["port"].as<unsigned short>();
    }
    if (varibaleMap.count("reservation")) {
        reservationCode = varibaleMap["reservation"].as<std::string>();
    }

    std::cout << "Parsing complete.\n";
    std::cout << "HostName: " + hostName + "\n";
    std::cout << "HostPort: " + std::to_string(hostPort) + "\n";
    std::cout << "ReservationCode: " + reservationCode + "\n";

    PiranhasClient piranhasClient;
    if (reservationCode.size() == 0) {
        std::cout << "Start.\n";
        piranhasClient.Start("127.0.0.1", hostPort);
    } else {
        std::cout << "Start reserved.\n";
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(hostName, "");
        for (boost::asio::ip::tcp::resolver::iterator i = resolver.resolve(query);
             i != boost::asio::ip::tcp::resolver::iterator();
             ++i) {
            boost::asio::ip::tcp::endpoint end = *i;
            std::cout << end.address() << ' ';
        }
        boost::asio::ip::tcp::resolver::iterator i = resolver.resolve(query);
        boost::asio::ip::tcp::endpoint endpoint = *i;
        piranhasClient.StartReserved(endpoint.address().to_string(), hostPort, reservationCode);
    }

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
