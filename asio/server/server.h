// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#pragma once
#include "server/cmdinterp.h"

#include <boost/asio.hpp>

#include <atomic>
#include <string>
#include <vector>

using boost::asio::ip::tcp;

struct Server
{
    Server() {}

    int boot(); 
    void handle_client(tcp::socket& socket, CmdInterp& interpreter);

private:
    void busy_task(); 
    void send_block(tcp::socket& socket);
    void register_commands(tcp::socket&);

    std::atomic<bool> busy_flag{true};
    std::atomic<bool> stop_flag{false};
    static const std::vector<std::string> progress;
    uint32_t progress_index=0;

    CmdInterp interpreter;
};
