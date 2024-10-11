// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#pragma once
#include "server/cmdinterp.h"

#include <boost/asio.hpp>

#include <atomic>
#include <string>
#include <variant>
#include <vector>

using boost::asio::ip::tcp;

struct Server
{
  using VariableType = std::variant<int64_t, 
                                    uint64_t, 
                                    bool,
                                    std::string,
                                    float,
                                    double>; 
  using ArgsType = const std::vector<std::string>;

  Server() {}

  int start(); 
  void handle_client(tcp::socket& socket, CmdInterp& interpreter);
    
private:
  void busy_task();

  void registration(tcp::socket&);
  //Command registration - registration.cpp
  void register_variable_cmds(tcp::socket&);
  void register_control_cmds(tcp::socket&);
  void register_info_cmds(tcp::socket&);

  //Variable registration - also registration.cpp
  void register_variables();
  void register_variable(const std::string& name, VariableType value) {
    variables[name] = value;
  }

  //Command implementation - commands.cpp
  void handle_help(tcp::socket& socket, ArgsType& args);
  void handle_set(tcp::socket& socket, ArgsType& args);
  void handle_show(tcp::socket& socket, ArgsType& args);
  void handle_sendblock(tcp::socket& socket, ArgsType& args);

  static const std::vector<std::string> progress;
  std::map<std::string, VariableType> variables;

  uint32_t progress_index=0;
  
  CmdInterp interpreter;

  std::string string_var = "";
  int int_var = 0;
  bool bool_var = false;

  // Flag to trigger server shutdown
  std::atomic<bool> shutdown_flag{false};
  std::atomic<bool> busy_flag{true};
  std::atomic<bool> stop_flag{false};

};
