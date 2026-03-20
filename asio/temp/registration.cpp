// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "server.h"
#include "common.h"
#include "commands.h"
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

// =======================================================================
// COMMANDS
// =======================================================================
void Server::registration(tcp::socket &socket) {
  register_user_cmds(command_map);
//  register_variable_cmds(socket);
//  register_info_cmds(socket);
  register_control_cmds(socket);

  register_variables();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Server::register_user_cmds(const ucmds::CommandMap& command_map) {
    for (const auto& [command, handler] : command_map) {
        // Wrap the handler to match the expected signature
        interpreter.register_command(command, [&socket, handler](const std::vector<std::string>& args) {
            handler(socket, args);
        });
    }
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Server::register_user_cmds(tcp::socket& socket) {
    // Register each command by adapting it to match the signature expected by the interpreter
    for (const auto& [command, handler] : command_map) {
        interpreter.register_command(command, [&socket, handler](const std::vector<std::string>& args) {
            handler(socket, args); // Call the original handler with the socket and args
        });
    }
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Server::register_control_cmds(tcp::socket &socket) {
  // STOP command -------------------------------------
  interpreter.register_command("stop", [this,&socket](ArgsType &args) {
    std::cout << "-I: Stopping server task..." << std::endl;
    busy_flag = false;
    boost::asio::write(socket, boost::asio::buffer("<1>"));
  });

  // RESTART command ----------------------------------
  interpreter.register_command("restart", [this,&socket](ArgsType &args) {
    std::cout << "-I: Resuming server task..." << std::endl;
    busy_flag = true;
    
    // If the stop_flag is set, the busy task has stopped, so restart it
    if (stop_flag) {
      stop_flag = false;  // Reset the stop flag to resume the task
      std::thread busy_thread(&Server::busy_task, this);
      busy_thread.detach();  // Detach the thread so it runs independently
    }
    boost::asio::write(socket, boost::asio::buffer("<1>"));
  });

  // SHUTDOWN command ----------------------------------
  interpreter.register_command("shutdown", [this,&socket](ArgsType &args) {
    std::cout << "-I: Shutting down server..." << std::endl;
    shutdown_flag = true;
    boost::asio::write(socket, boost::asio::buffer("<1>"));
  });

}
    // Define a map of CommandHandler, matching the signature (tcp::socket&, ArgsType&)
std::map<std::string, Server::CommandHandler> command_map = {
  {"help", [this](tcp::socket& s, Server::ArgsType& args) { Server::handle_help(s, args); }},
  {"?", [this](tcp::socket& s, Server::ArgsType& args) { Server::handle_help(s, args); }},
  {"sendblock", [this](tcp::socket& s, Server::ArgsType& args) { Server::handle_sendblock(s, args); }},
  {"set", [this](tcp::socket& s, Server::ArgsType& args) { Server::handle_set(s, args); }},
  {"show", [this](tcp::socket& s, Server::ArgsType& args) { Server::handle_show(s, args); }}
};
// =======================================================================
// VARIABLES
// =======================================================================
void Server::register_variables() 
{
  register_variable("int_var",    int64_t(0));
  register_variable("uint_var",   uint64_t(0));
  register_variable("bool_var",   bool(false));
  register_variable("string_var", std::string(""));
  register_variable("float_var",  float(0.0));
  register_variable("double_var", double(0.0));
}
