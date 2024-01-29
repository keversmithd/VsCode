#include <asio.hpp>
#include <iostream>
#include <vector>
struct async_server
{
public:
    asio::io_context m_io_context;
    asio::ip::tcp::acceptor m_acceptor;
    std::vector<std::shared_ptr<asio::ip::tcp::socket>> m_sockets;
public:
    async_server() : m_acceptor(m_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 13))
    {
        startAccepting();
        std::cout << "Started Server: " << std::endl;
        m_io_context.run();
    }

    void startAccepting()
    {
        m_acceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket){
            if(!ec)
            {
                m_sockets.push_back(std::make_shared<asio::ip::tcp::socket>(std::move(socket)));
                handleClient(m_sockets.back());
                startAccepting();
            }else{
                std::cout << "Missed a connection: " << ec.message() << std::endl;
                startAccepting();
            }
        });

        

    }

    void handleClient(std::shared_ptr<asio::ip::tcp::socket> socket)
    {
        try {
            // Receive data from the client
            std::array<char, 128> buffer;
            socket->async_read_some(asio::buffer(buffer),[&buffer](std::error_code ec, std::size_t bytes_transferred){
                if(!ec)
                {
                    //Print the received message
                    std::cout << "Received message from client: " << std::string(buffer.data(), bytes_transferred) << std::endl;

                }else
                {
                    std::cout << "Shitty message" << std::endl;
                }
            });



        } catch (std::exception& e) {
            std::cerr << "Exception in client handler: " << e.what() << std::endl;
        }
    }
};


int main()
{
    async_server server;

    // while(1)
    // {

    // }

    
    

    return 0;
}
