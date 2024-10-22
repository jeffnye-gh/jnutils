// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "client.h"
#include "common.h"
#include <thread>
#include <chrono>
#include <string>
#include <fstream>

using boost::asio::ip::tcp;
using namespace std;

// -------------------------------------------------------------------
// -------------------------------------------------------------------
bool Client::isCommand(const string &str)
{
  if(str.empty()) return false;

  auto it = std::find_if(str.begin(), str.end(), [](char ch) {
    return !std::isspace(static_cast<unsigned char>(ch));
  });

  return !(it != str.end() && *it == '#');
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
uint32_t Client::connect()
{
    stop_on_error = true;

    std::string command_name;
    std::vector<std::string> args;
    std::string arg;

    while (true) {
        try {
            boost::asio::io_context io_context;

            // Connect to the server
            tcp::resolver resolver(io_context);
            tcp::resolver::results_type endpoints
                = resolver.resolve(Comms::get_ip(), Comms::get_port());

            tcp::socket socket(io_context);
            boost::asio::connect(socket, endpoints);

            cout << "-I: Connected to server: " << Comms::get_comms() << endl;

            while (true) {
                // Get the command from the user
                string command;
                cout << prompt;
                getline(cin, command);

                if(command.empty()) continue;

                if (command == "shutdown") {
                    cout << "-I: Client shutting down..." << endl;
                    return 0;  // Exit the client
                }

                if (command == "exit") {
                    cout << "-I: Client exiting..." << endl;
                    return 0;  // Exit the client
                }

                std::istringstream iss(command);
                iss >> command_name;
                args.clear();

                while(iss >> arg) args.push_back(arg);

                if (command_name == "cset") {
                    handle_cset(args);
                    continue;
                }

                if (command_name == "csrc") {
                    handle_csrc(socket,args);
                    continue;
                }

                send_command(socket, command);
            }
        } catch (exception& e) {
            cout << "-W: Connection failed: " << e.what() << endl;
            cout << "-I: Retrying in " << Comms::retry_wait 
                                       << " seconds..." << endl;
            this_thread::sleep_for(chrono::seconds(Comms::retry_wait));
        }
    }

    return 0;
}

