// --------------------------------------------------------------------------
// This file is part of jnutils, made public 2023-24, (c) Jeff Nye
//
// jnutils is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// jnutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with jnutils; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
// ---------------------------------------------------------------------------
#include "msg.h"
#include "gdbserver.h"

using namespace std;

bool GbdServer::start()
{
  // Create socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    msg->emsg("-E: Failed to create socket");
    return false;
  }

  // Bind to the specified port
  sockaddr_in server_addr {};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    msg->emsg("-E: Failed to bind socket");
    return false;
  }

  // Listen for incoming connections
  if (listen(server_fd, 1) < 0) {
    msg->emsg("-E: Failed to listen on socket");
    return false;
  }

  msg->imsg("-I: GDB server listening on port "+::to_string(port));

  // Accept a connection
  sockaddr_in client_addr {};
  socklen_t client_len = sizeof(client_addr);
  client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
  if (client_fd < 0) {
    msg->emsg("-I: Failed to accept connection");
    return false;
  }

  msg->imsg("-I: GDB client connected");
  return true;
}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
bool GbdServer::handleClient()
{
  char buffer[1024];
  while (true) {
    // Read data from GDB client
    ssize_t len = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (len <= 0) {
      msg->emsg("-E: Failed to receive data or connection closed");
      break;
    }

    buffer[len] = '\0';  // Null-terminate the received data
    std::string command(buffer);
    msg->imsg("-I: Received command: '"+command+"'");

    // Handle GDB commands (simple example)
    if (command == "?") {
      // Send a response indicating the target state is stopped
      sendResponse("S05");
    } else if (command == "g") {
      // Read all registers and send a dummy response
      // Example for 4 registers
      sendResponse("00000000000000000000000000000000"); 
    } else {
      // Unrecognized command
      sendResponse("");
    }
  }
}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void GdbServer::sendResponse(const std::string& response) {
  // Send response in the format $<data>#<checksum>
  std::string packet = "$" + response + "#" + calculateChecksum(response);
  send(client_fd, packet.c_str(), packet.size(), 0);
}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
std::string GdbServer::calculateChecksum(const std::string& data) {
  unsigned char checksum = 0;
  for (char c : data) {
      checksum += c;
  }
  char checksum_str[3];
  snprintf(checksum_str, sizeof(checksum_str), "%02x", checksum);
  return checksum_str;
}

