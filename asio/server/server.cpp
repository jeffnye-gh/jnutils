// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "server.h"
#include "common.h"
#include <iostream>
#include <thread>

const std::vector<std::string> Server::progress = { "|", "/", "-", "\\" };

using namespace std;

int Server::start() {
  try {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context,
                           tcp::endpoint(tcp::v4(), Comms::tcpport));

    std::cout << "-I: Server listening on connection: " 
              << Comms::tcpport << std::endl;

    shutdown_flag = false;

    while (!shutdown_flag) {
      tcp::socket socket(io_context);

      // Wait for a client connection
      std::cout << "-I: Waiting for client connection..." << std::endl;
      acceptor.accept(socket);

      std::cout << "-I: Client connected." << std::endl;

      // Start busy task in a separate thread
      std::thread busy_thread(&Server::busy_task, this);

      // Register known commands
      registration(socket);

      try {
          // Handle client connection and commands
          handle_client(socket, interpreter);
      } catch (std::exception& e) {
          std::cerr << "-E: Client connection error: "<< e.what() << std::endl;
      }

      // Clean up after client disconnects
      stop_flag = true;
      busy_thread.join();  // Wait for the busy thread to finish
      stop_flag = false;   // Reset stop_flag for future clients
    }

    std::cout << "-I: Server shutdown complete." << std::endl;
    exit(0);
  } catch (std::exception& e) {
      std::cerr << "-E: Server error: " << e.what() << std::endl;
  }

  return 0;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Server::busy_task() {
  while (!stop_flag) {
    if (busy_flag) {
      string prog = progress[progress_index&0x3];
      cout << "-I: Server process is busy: "<<prog<<"\r"; 
      cout.flush();
      ++progress_index;
      this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
  cout << "-I: Server process is paused." << endl;
}

