#pragma once

#include <boost/asio.hpp>

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using boost::asio::ip::tcp;

// Command interpreter class that handles the execution of commands
class CmdInterp {
public:
    using FuncVoidType = std::function<void(const std::vector<std::string>&)>;
    using MapFuncVoidType = std::map<std::string,FuncVoidType>;

    // Register command 
    void register_command(const std::string& name,const FuncVoidType & func)
    {
      commands[name] = func;
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
