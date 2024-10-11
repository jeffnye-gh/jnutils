// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#pragma once

#include <boost/asio.hpp>

#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using boost::asio::ip::tcp;

struct CmdInterp {

  using FuncVoidType = std::function<void(const std::vector<std::string>&)>;
  using MapFuncVoidType = std::map<std::string,FuncVoidType>;

  // Register command 
  void register_command(const std::string& name,const FuncVoidType & func)
  {
    commands[name] = func;
  }

  // New register_command to accept multiple commands
  void register_mcommand(const std::vector<std::string>& names,
                        const FuncVoidType & func)
  {
    for (const auto& name : names) {
        commands[name] = func;
    }
  }

  // Execute the command based on the input
  void execute_command(const std::string& input) {
    std::istringstream iss(input);
    std::string command_name;
    iss >> command_name;

    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    // Find and execute the command
    if (commands.find(command_name) != commands.end()) {
        commands[command_name](args);
    } else {
        std::cerr << "Unknown command: " << command_name << std::endl;
    }
  }

private:
  MapFuncVoidType commands;
};
