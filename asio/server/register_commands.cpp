// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "server.h"
#include "common.h"
#include <vector>
#include <iostream>

extern std::atomic<bool> busy_flag;
using namespace std;
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Server::register_commands(tcp::socket &socket)
{
    // Register 'stop' command to stop busy work
    interpreter.register_command("stop",
                [this](const vector<string>& args)
    {
       cout << "Stopping server task..." << endl;
       busy_flag = false;
    });

    // Register 'sendblock' command to send a block of text
    interpreter.register_command("sendblock",
                [this, &socket](const vector<string>& args)
    {
        cout << "Block send..." << endl;
        send_block(socket);
    });

    // Register 'restart' command to restart the busy task
    interpreter.register_command("restart",
                [this](const vector<string>& args) {
        cout << "Resuming server task..." << endl;
        busy_flag = true;
    });

}

