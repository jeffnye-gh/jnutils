#include "server.h"

#include <iostream>
#include <boost/asio.hpp>

// Function to split input into command and arguments
void Server::handle_client(tcp::socket& socket, CmdInterp& interpreter) {
    try {
        char data[1024];
        boost::system::error_code error;

        while (true) {
            // Read client data
            size_t length = socket.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof)
                break; // Connection closed by the client
            else if (error)
                throw boost::system::system_error(error);

            // Null-terminate the received data
            data[length] = '\0';

            // Execute the received command
            interpreter.execute_command(std::string(data));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

