#include "server.h"
#include "common.h"
#include <iostream>
#include <thread>

using namespace std;

const std::vector<std::string> Server::progress = { "|", "/", "-", "\\" };

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
int Server::boot() {

  try {
    boost::asio::io_context io_context;

    // Create a TCP server that listens on port 12345
    tcp::acceptor acceptor(io_context,
                           tcp::endpoint(tcp::v4(), Comms::tcpport));

    cout << "Server listening: " << Comms::get_comms() << endl;

    tcp::socket socket(io_context);
    acceptor.accept(socket);

    cout << "Client connected!" << endl;

    // Start busy task in a separate thread
    thread busy_thread(&Server::busy_task, this);

    register_commands(socket);

    // Handle client connection and commands
    handle_client(socket, interpreter);

    // Set the stop flag and wait for the busy thread to finish
    stop_flag = true;
    busy_thread.join();

  } catch (exception& e) {
    cerr << "Exception: " << e.what() << endl;
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
    std::cout << "Server stopped working." << std::endl;
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Server::send_block(tcp::socket& socket) {
    std::string block =
        "X0  0x0000000000000000 | X16 0x0000000000000000\n"
        "X1  0x0000234987234000 | X17 0x0000234987234000\n"
        "X2  0xaaabdbdbd3434340 | X18 0xaaabdbdbd3434340\n"
        "X3  0x123456789abcdef0 | X19 0x123456789abcdef0\n"
        "X4  0x123456789abcdef0 | X20 0x123456789abcdef0\n"
        "X5  0x123456789abcdef0 | X21 0x123456789abcdef0\n"
        "X6  0x123456789abcdef0 | X22 0x123456789abcdef0\n"
        "X7  0x123456789abcdef0 | X23 0x123456789abcdef0\n"
        "X8  0x123456789abcdef0 | X24 0x123456789abcdef0\n"
        "X9  0x123456789abcdef0 | X25 0x123456789abcdef0\n"
        "X10 0x123456789abcdef0 | X26 0x123456789abcdef0\n"
        "X11 0x123456789abcdef0 | X27 0x123456789abcdef0\n"
        "X12 0x123456789abcdef0 | X28 0x123456789abcdef0\n"
        "X13 0x123456789abcdef0 | X29 0x123456789abcdef0\n"
        "X14 0x123456789abcdef0 | X30 0x123456789abcdef0\n"
        "X15 0x123456789abcdef0 | X31 0x123456789abcdef0\n";

    boost::asio::write(socket, boost::asio::buffer(block));
}
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
