// --------------------------------------------------------------------------
// This file is part of jnutils, made public 2023, (c) Jeff Nye
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
#include <string>
#include <thread>
#include <functional>

class Client {

public:
  ~Client();
  bool operator ==(const Client & other);

  void setFileDescriptor(int sockfd) { m_sockfd = sockfd; }
  int getFileDescriptor() const { return m_sockfd; }

  void setIp(const std::string & ip) { m_ip = ip; }
  std::string getIp() const { return m_ip; }

  void setErrorMessage(const std::string & msg) { m_errorMsg = msg; }
  std::string getInfoMessage() const { return m_errorMsg; }

  void setConnected() { m_isConnected = true; }

  void setDisconnected() { m_isConnected = false; }
  bool isConnected() { return m_isConnected; }

  void setThreadHandler(std::function<void(void)> func) {
    m_threadHandler = new std::thread(func);
  }

private:
  int m_sockfd = 0;
  std::string m_ip = "";
  std::string m_errorMsg = "";
  bool m_isConnected;
  std::thread * m_threadHandler = nullptr;

};
