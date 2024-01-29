#include <asio.hpp>
#include <iostream>

class async_client
{
private:
    asio::ip::tcp::socket socket;
    asio::ip::tcp::resolver resolver;
    bool connected;
public:
    async_client(asio::io_service& io_service, const std::string& server, const std::string& port) : resolver(io_service), socket(io_service), connected(false)
    {
        asio::ip::tcp::resolver::query query(server, port);
        resolver.async_resolve(query,
        [this](const asio::error_code& error, asio::ip::tcp::resolver::results_type endpoints)
        {
            handle_resolve(error, endpoints);
        });

        io_service.run();
    }


    void handle_resolve(const asio::error_code& error, asio::ip::tcp::resolver::results_type endpoints)
    {
        if (!error)
        {
            std::cout << "Success, connecting." << std::endl;
            connect(endpoints);
        }
        else
        {
            std::cout << "Error resolving host: " << error.message() << std::endl;
        }
    }

    void connect(asio::ip::tcp::resolver::results_type endpoints)
    {
        asio::async_connect(socket, endpoints,
            [this](const asio::error_code& ec, asio::ip::tcp::endpoint endpoint)
            {
                if (!ec)
                {
                    std::cout << "Connected." << std::endl;
                    this->connected = true;
                    pingserver();
                }
                else
                {
                    std::cout << "Exception: " << ec.message() << std::endl;
                }
            });
    }

    void pingserver()
    {
        if (connected)
        {
            std::string message = "Hello, server!";
            asio::async_write(socket, asio::buffer(message),
                [](const asio::error_code& ec, std::size_t /*bytes_transferred*/)
                {
                    if (!ec)
                    {
                        std::cout << "Message sent." << std::endl;
                    }
                    else
                    {
                        std::cout << "Error sending message: " << ec.message() << std::endl;
                    }
                });
        }
        else
        {
            std::cout << "No server connection." << std::endl;
        }
    }
};




int main()
{
    try {
        
        asio::io_context io_context;
        async_client client(io_context, "127.0.0.1", "13");
        
        

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }





    return 0;
}