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
#pragma once
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

class GdbServer {
public:
  GdbServer(int port)
    : port(port),
      server_fd(-1),
      client_fd(-1)
  {}

  bool start();
  void handleClient();
  void sendResponse(const std::string& response);
  std::string calculateChecksum(const std::string& data);

  void stop() {
    if (client_fd != -1) close(client_fd);
    if (server_fd != -1) close(server_fd);
  }

private:
    int port;
    int server_fd;
    int client_fd;
};

int main() {
    GdbServer server(1234);
    if (!server.start()) {
        std::cerr << "Failed to start GDB server\n";
        return 1;
    }
    server.handleClient();
    server.stop();
    return 0;
}
