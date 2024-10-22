// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "server.h"

#include <iostream>
#include <boost/asio.hpp>
using namespace std;

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
      interpreter.execute_command(string(data),socket);
    }
  } catch (exception& e) {
      cerr << "Exception: " << e.what() << endl;
  }
}

