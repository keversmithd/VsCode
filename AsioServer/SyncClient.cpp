#include <asio.hpp>
#include <iostream>
#include <chrono>
using namespace std::chrono;



int main() {
    try {
        asio::io_context io_context;

        asio::ip::tcp::socket socket(io_context);

        asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "13");

        asio::connect(socket, endpoints);

        int z = 0;
        for(int i = 0; i < 100; i++)
        {
            asio::write(socket, asio::buffer(&z, sizeof(int)));
        }
        
        socket.close();
        io_context.stop();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
