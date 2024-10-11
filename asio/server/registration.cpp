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
  register_variable_cmds(socket);
  register_info_cmds(socket);
  register_control_cmds(socket);

  register_variables();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Server::register_control_cmds(tcp::socket &socket) {

  // STOP -------------------------------------
  interpreter.register_command("stop", [this](ArgsType &args)
  {
    cout << "-I: Stopping server task..." << endl;
    busy_flag = false;
  });

  // RESTART ----------------------------------
  interpreter.register_command("restart",[this](ArgsType& args)
  {
    cout << "-I: Resuming server task..." << endl;
    busy_flag = true;
  });

  // SHUTDOWN ----------------------------------
  interpreter.register_command("shutdown",[this](ArgsType &args)
  {
    cout << "-I: Shutting down server..." << endl;
    shutdown_flag = true;
  });

  boost::asio::write(socket, boost::asio::buffer("<1>"));

}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Server::register_info_cmds(tcp::socket &socket) {
  // HELP -------------------------------------
  interpreter.register_mcommand({"help","?"},[this, &socket](ArgsType& args)
  {
    handle_help(socket,args);
  });

  // SENDBLOCK --------------------------------
  interpreter.register_command("sendblock",[this, &socket](ArgsType &args)
  {
    //cout << "-I: Block send..." << endl;
    handle_sendblock(socket,args);
  });
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Server::register_variable_cmds(tcp::socket &socket)
{
  // SET --------------------------------------
  interpreter.register_command("set",[this, &socket](ArgsType& args)
  {
    handle_set(socket, args);
  });

  // SHOW -------------------------------------
  interpreter.register_command("show",[this, &socket](ArgsType& args)
  {
    handle_show(socket, args);
  });
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
