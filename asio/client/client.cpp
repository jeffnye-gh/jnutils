// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "client.h"
#include "common.h"
#include <thread>
#include <chrono>
#include <string>

using boost::asio::ip::tcp;
using namespace std;

uint32_t Client::connect()
{
  while (true) {
    try {
      boost::asio::io_context io_context;

      // Connect to the server
      tcp::resolver resolver(io_context);
      tcp::resolver::results_type endpoints
         = resolver.resolve(Comms::get_ip(),Comms::get_port());

      tcp::socket socket(io_context);
      boost::asio::connect(socket, endpoints);

      cout << "Connected to server!" << endl;

      while (true) {
        // Get the command from the user
        string command;
        cout << prompt;
        getline(cin, command);

        if (command == "exit") {
            break;
        }

        // Send the command to the server
        boost::asio::write(socket, boost::asio::buffer(command + "\n"));

        // Check if the command was 'sendblock' to receive data back
        if (command == "sendblock") {
          char data[2048];
          boost::system::error_code error;

          // Read the response from the server
          size_t length = socket.read_some(boost::asio::buffer(data), error);
          if (error == boost::asio::error::eof) {
              break;  // Server closed connection
          } else if (error) {
              throw boost::system::system_error(error);  // Other errors
          }

          // Null-terminate the received data and print it
          data[length] = '\0';
          cout << "Received from server:\n" << data << endl;
        }
      }
    } catch (exception& e) {
      cerr << "Connection failed: " << e.what() << endl;
      cout << "Retrying in 5 seconds..." << endl;
      this_thread::sleep_for(chrono::seconds(Comms::retry_wait)); 
    }
  }

  return 0;
}

