// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#pragma once

#include "mfmtcp_defs.h"
#include "client.h"
#include "server_observer.h"
#include "pipe_ret_t.h"

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <functional>
#include <cstring>
#include <errno.h>
#include <iostream>

class TcpServer
{
public:

  pipe_ret_t start(int port);
  Client acceptClient(uint timeout);
  bool deleteClient(Client & client);
  void subscribe(const server_observer_t & observer);
  void unsubscribeAll();
  pipe_ret_t sendToAllClients(const char * msg, size_t size);
  pipe_ret_t sendToClient(const Client & client, const char * msg, size_t size);
  pipe_ret_t finish();
  void printClients();

private:
  int m_sockfd;
  struct sockaddr_in m_serverAddress;
  struct sockaddr_in m_clientAddress;
  fd_set m_fds;
  std::vector<Client> m_clients;
  std::vector<server_observer_t> m_subscibers;
  std::thread * threadHandle;

  void publishClientMsg(const Client & client, const char * msg, size_t msgSize);
  void publishClientDisconnected(const Client & client);
  void receiveTask(/*void * context*/);
};
