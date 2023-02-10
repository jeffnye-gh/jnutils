// --------------------------------------------------------------------
// Derived from the original code ceated by erauper on 4/7/19.
// See https://github.com/elhayra/tcp_server_client
// Subsequently modified for my use.
// --------------------------------------------------------------------
// Modifications: Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#pragma once

#include "mfmtcp_defs.h"
#include "client_observer.h"
#include "pipe_ret_t.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netdb.h>
#include <vector>
#include <errno.h>
#include <thread>

// ==============================================================================
// ==============================================================================
class TcpClient
{
private:
    int m_sockfd = 0;
    bool stop = false;
    struct sockaddr_in m_server;
    std::vector<client_observer_t> m_subscibers;
    std::thread * m_receiveTask = nullptr;

    void publishServerMsg(const char * msg, size_t msgSize);
    void publishServerDisconnected(const pipe_ret_t & ret);
    void ReceiveTask();
    void terminateReceiveThread();

public:
    ~TcpClient();
    pipe_ret_t connectTo(const std::string & address, int port);
    pipe_ret_t sendMsg(const char * msg, size_t size);

    void subscribe(const client_observer_t & observer);
    void unsubscribeAll();
    void publish(const char * msg, size_t msgSize);

    pipe_ret_t finish();
};
