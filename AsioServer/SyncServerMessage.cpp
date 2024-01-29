#include <asio.hpp>
#include <iostream>

enum MessageHeader
{
    PING_SERVER = 0
};

template<typename T>
struct MessageBody
{

};


struct SyncServer
{
    asio::io_context m_io_context;
    asio::ip::tcp::acceptor acceptor;
    std::vector<asio::ip::tcp::socket> connections;

    SyncServer() : acceptor(m_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 13))
    {
        StartAccepting();
    }

    void StartAccepting()
    {
        while(true)
        {
            asio::ip::tcp::socket socket(m_io_context);
            acceptor.accept(socket);

            read_header(socket);
        }
    }


    void read_header(asio::ip::tcp::socket& socket)
    {
        try {
            // Receive data from the client
            MessageHeader buffer;
            asio::read(socket, asio::buffer(&buffer, sizeof(MessageHeader)));
            read_body(buffer, socket);
            // Print the received message
            std::cout << "Received instruction from the client handling message." << std::endl;

        } catch (std::exception& e) {
            std::cerr << "Exception in client handler: " << e.what() << std::endl;
        }
    }


    void read_body(MessageHeader header, asio::ip::tcp::socket& socket)
    {
        switch(header)
        {
            case PING_SERVER:
                    std::cout << "I am pinging server! " << std::endl; 
                break;

            default:
                break;
        }
    }

};

int main()
{
    SyncServer server;

    

    return 0;
}
