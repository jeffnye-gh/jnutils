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
  void register_cmds(tcp::socket&);

  //Variable registration - also registration.cpp
  void register_variables();
  void register_variable(const std::string& name, VariableType value) {
    variables[name] = value;
  }

  std::string tq(std::string s) { return "'"+s+"'"; }

  //Command implementation - commands.cpp
  #define _STDARGS_ tcp::socket &socket,ArgsType &args
  void handle_help    (_STDARGS_);
  void handle_info    (_STDARGS_);
  void handle_restart (_STDARGS_);
  void handle_regs    (_STDARGS_);
  void handle_set     (_STDARGS_);
  void handle_show    (_STDARGS_);
  void handle_shutdown(_STDARGS_);
  void handle_stop    (_STDARGS_);

  void info_regs(_STDARGS_);
  void info_breakpoints(_STDARGS_);
  void info_variables(_STDARGS_);

  std::string strResp(bool good,std::string s) {
    return good ? "-I:G:STRING:"+s : "-E:G:STRING:"+s;
  }

  std::string retCode(bool good) {
    return good ? "-I:RET:STRING:<1>" : "-E:RET:STRING:<0>";
  }

  void too_few_args(std::string,_STDARGS_);
  void unknown_subcommand(std::string,_STDARGS_);
  void unimplemented_command(std::string,_STDARGS_);
  #undef  _STDARGS_ 

  // --------------------------------------------------------------------
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

  std::map<std::string, std::function<void(tcp::socket&, ArgsType&)>> 
       user_command_map;
};
