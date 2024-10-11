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
