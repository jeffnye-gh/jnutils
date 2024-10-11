// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "server.h"
#include "common.h"
#include <iostream>
#include <thread>

std::atomic<bool> busy_flag{true};
std::atomic<bool> stop_flag{false};
const std::vector<std::string> Server::progress = { "|", "/", "-", "\\" };

using namespace std;

int Server::boot() {
  try {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context,
              tcp::endpoint(tcp::v4(), Comms::tcpport));

    cout << "Server listening on port " << Comms::tcpport << endl;

    while (true) {
      tcp::socket socket(io_context);

      // Wait for a client connection
      cout << "Waiting for client connection..." << endl;
      acceptor.accept(socket);

      cout << "Client connected!" << endl;

      // Command interpreter setup
      //CmdInterp interpreter;

      // Start busy task in a separate thread
      std::thread busy_thread(&Server::busy_task, this);

      register_commands(socket);

      try {
          // Handle client connection and commands
          handle_client(socket, interpreter);
      } catch (std::exception& e) {
          cerr << "Client connection error: " << e.what() << endl;
      }

      // Clean up after client disconnects
      stop_flag = true;
      busy_thread.join();
      stop_flag = false;  // Reset stop_flag for future clients
    }
  } catch (std::exception& e) {
      cerr << "Server error: " << e.what() << endl;
  }

  return 0;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Server::busy_task() {
  while (!stop_flag) {
    if (busy_flag) {
      string prog = progress[progress_index&0x3];
      cout << "Server is busy doing some work: "<<prog<<"\r"; 
      cout.flush();
      ++progress_index;
      this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
  cout << "Server stopped working." << endl;
}
