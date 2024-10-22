// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "server.h"
#include "common.h"
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

// =======================================================================
// COMMANDS
// =======================================================================
void Server::registration(tcp::socket &socket) {
  register_variables();
  register_cmds(socket);
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Server::register_cmds(tcp::socket& socket) {
  // Populate the map with command handlers
  user_command_map = {
    {"help", [this](tcp::socket& socket, ArgsType& args) { handle_help(socket, args); }},
    {"?", [this](tcp::socket& socket, ArgsType& args) { handle_help(socket, args); }},
    {"restart", [this](tcp::socket& socket, ArgsType& args) { handle_restart(socket, args); }},
    {"sendblock", [this](tcp::socket& socket, ArgsType& args) { handle_sendblock(socket, args); }},
    {"set", [this](tcp::socket& socket, ArgsType& args) { handle_set(socket, args); }},
    {"show", [this](tcp::socket& socket, ArgsType& args) { handle_show(socket, args); }},
    {"shutdown", [this](tcp::socket& socket, ArgsType& args) { handle_shutdown(socket, args); }},
    {"stop", [this](tcp::socket& socket, ArgsType& args) { handle_stop(socket, args); }}

  };

  // Iterate over the map and register each command with the interpreter
  for (const auto& [command_name, handler] : user_command_map) {
    interpreter.register_command(command_name, [this, &socket, handler](ArgsType& args) {
      handler(socket, args);
    });
  }
}
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
