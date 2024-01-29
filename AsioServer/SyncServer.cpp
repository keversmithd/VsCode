#include <asio.hpp>
#include <iostream>

void handle_client(asio::ip::tcp::socket& socket)
{
    try {
        // Receive data from the client
        std::array<char, 128> buffer;
        std::size_t bytes_transferred = socket.read_some(asio::buffer(buffer));

        // Print the received message
        std::cout << "Received message from client: " << std::string(buffer.data(), bytes_transferred) << std::endl;

        // Send a response back to the client
        std::string response = "Hello, client!";
        asio::write(socket, asio::buffer(response));
    } catch (std::exception& e) {
        std::cerr << "Exception in client handler: " << e.what() << std::endl;
    }
}

int main()
{
    
    try {
        asio::io_context io_context;
        

        // Create an acceptor to listen for incoming connections
        asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 13));

        std::cout << "Server started and listening on port " << 13 << std::endl;

        while (true) {
            asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
        
            // Handle the client connection in a separate thread
            handle_client(socket);
        }
        
    } catch (std::exception& e) {
        std::cerr << "Exception in server: " << e.what() << std::endl;
    }

    return 0;
}
