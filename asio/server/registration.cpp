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
#define IARGS tcp::socket& socket,ArgsType& args
#define HARGS socket,args
// -----------------------------------------------------------------------
void Server::register_cmds(tcp::socket& socket) {
  // Populate the map with command handlers
  user_command_map = {
    {"help",    [this](IARGS) { handle_help(HARGS); }},
    {"?",       [this](IARGS) { handle_help(HARGS); }},
    {"info",    [this](IARGS) { handle_info(HARGS); }},
    {"restart", [this](IARGS) { handle_restart(HARGS); }},
    {"set",     [this](IARGS) { handle_set(HARGS); }},
    {"show",    [this](IARGS) { handle_show(HARGS); }},
    {"shutdown",[this](IARGS) { handle_shutdown(HARGS); }},
    {"stop",    [this](IARGS) { handle_stop(HARGS); }}

  };

  // Iterate over the map and register each command with the interpreter
  for (const auto& [command_name, handler] : user_command_map) {
    interpreter.register_command(command_name,
      [this, &socket, handler](ArgsType& args)
        {
          handler(socket, args);
        }
    );
  }
}
#undef IARGS
#undef HARGS
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
