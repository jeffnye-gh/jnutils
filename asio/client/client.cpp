#include "common.h"
#include "client.h"

using boost::asio::ip::tcp;
using namespace std;

uint32_t Client::connect()
{
    try {
        boost::asio::io_context io_context;

        // Connect to the server on localhost:12345
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = 
                       resolver.resolve(Comms::hostip,::to_string(Comms::tcpport));

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        cout << "Connected to server:"<<Comms::hostip <<":"
                                <<::to_string(Comms::tcpport)<< endl;

        while (true) {
            // Get the command from the user
            string command;
            cout << prompt;
            getline(cin, command);

            if (command == "exit") { break; }

            // Send the command to the server
            boost::asio::write(socket, boost::asio::buffer(command + "\n"));

            // Check if the command was 'sendblock' to receive data back
            if (command == "sendblock") {
                char data[1024];
                boost::system::error_code error;

                // Read the response from the server
                size_t length = socket.read_some(boost::asio::buffer(data), error);
                if (error == boost::asio::error::eof) {
                    break; // Connection closed by server
                } else if (error) {
                    throw boost::system::system_error(error);
                }

                // Null-terminate the received data and print it
                data[length] = '\0';
                cout << "Received from server:\n" << data << endl;
            }
        }
    } catch (exception &e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}


//#include "client.h"
//
//using boost::asio::ip::tcp;
//
//uint32_t Client::connect()
//{
//    try {
//        boost::asio::io_context io_context;
//
//        // Connect to the server on localhost:12345
//        tcp::resolver resolver(io_context);
//        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "12345");
//
//        tcp::socket socket(io_context);
//        boost::asio::connect(socket, endpoints);
//
//        std::cout << "Connected to server!" << std::endl;
//
//        while (true) {
//            // Get the command from the user
//            std::string command;
//            std::cout << prompt;
//            std::getline(std::cin, command);
//
//            if (command == "exit") { break; }
//
//            // Send the command to the server
//            boost::asio::write(socket, boost::asio::buffer(command + "\n"));
//
//            // Check if the command was 'fibo' to receive data back
//            if (command.find("fibo") == 0) {
//                char data[1024];
//                boost::system::error_code error;
//
//                // Read the response from the server
//                size_t length = socket.read_some(boost::asio::buffer(data), error);
//                if (error == boost::asio::error::eof) {
//                    break; // Connection closed by server
//                } else if (error) {
//                    throw boost::system::system_error(error);
//                }
//
//                // Null-terminate the received data and print it
//                data[length] = '\0';
//                std::cout << "Received from server: " << data << std::endl;
//            }
//        }
//    } catch (std::exception &e) {
//        std::cerr << "Exception: " << e.what() << std::endl;
//    }
//
//    return 0;
//}
//
//
