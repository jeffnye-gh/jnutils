// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "server.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;
// =====================================================================
// Error messages
// =====================================================================
void Server::too_few_args(string cmd, tcp::socket &socket, ArgsType &args)
{
  (void) socket;
  (void) args;

  string response = "Too few arguments for command "+tq(cmd);
  boost::asio::write(socket, boost::asio::buffer(response));
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Server::unknown_subcommand(string base,tcp::socket &socket, ArgsType &args)
{
  string response = "Unknown subcommand "+tq(args[0])+" for command "+tq(base);
  boost::asio::write(socket, boost::asio::buffer(response));
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Server::unimplemented_command(string base,tcp::socket &socket, ArgsType &args)
{
  string response = "Command "+tq(base)+"::"+tq(args[0] 
                  +" has not been implemented");
  boost::asio::write(socket, boost::asio::buffer(response));
}
// =====================================================================
// HHH
// =====================================================================
void Server::handle_help(tcp::socket &socket, ArgsType &args)
{
  string response = "Help message\n";
  boost::asio::write(socket, boost::asio::buffer(response));
}
// =====================================================================
// III
// =====================================================================
void Server::handle_info(tcp::socket &socket, ArgsType &args)
{
  if(args.size() == 0) { return too_few_args("info",socket,args); }

  if(args[0] == "regs" || args[0] == "registers") {
    info_regs(socket,args);
  } else if(args[0] == "b" || args[0] == "breakpoints") {
    info_breakpoints(socket,args);
  } else if(args[0] == "vars" || args[0] == "variables") {
    info_variables(socket,args);
  } else {
    unknown_subcommand("info",socket,args);
  }
}
// ---------------------------------------------------------------------
// INFO - Breakpoints
// ---------------------------------------------------------------------
void Server::info_breakpoints(tcp::socket &socket, ArgsType &args)
{
  unimplemented_command("info",socket,args);
//  string response = "Info "+tq(args[0]);
//  boost::asio::write(socket, boost::asio::buffer(response));
}
// ---------------------------------------------------------------------
// INFO - REGS
// ---------------------------------------------------------------------
void Server::info_regs(tcp::socket &socket,ArgsType&)
{
  string block =
    "X0  0x0000000000000000 | X16 0x0000000000000000 | mstatus  0x12345678 \n"
    "X1  0x0000234987234000 | X17 0x0000234987234000 | mcause   0x12345678 \n"
    "X2  0xaaabdbdbd3434340 | X18 0xaaabdbdbd3434340 | mepc     0x12345678 \n"
    "X3  0x123456789abcdef0 | X19 0x123456789abcdef0 | mtval    0x12345678 \n"
    "X4  0x123456789abcdef0 | X20 0x123456789abcdef0 | mie      0x12345678 \n"
    "X5  0x123456789abcdef0 | X21 0x123456789abcdef0 | mscratch 0x12345678 \n"
    "X6  0x123456789abcdef0 | X22 0x123456789abcdef0 | mstatus  0x12345678 \n"
    "X7  0x123456789abcdef0 | X23 0x123456789abcdef0 | mtime    0x12345678 \n"
    "X8  0x123456789abcdef0 | X24 0x123456789abcdef0 | mtimecmp 0x12345678 \n"
    "X9  0x123456789abcdef0 | X25 0x123456789abcdef0 | sstatus  0x12345678 \n"
    "X10 0x123456789abcdef0 | X26 0x123456789abcdef0 | scause   0x12345678 \n"
    "X11 0x123456789abcdef0 | X27 0x123456789abcdef0 | sepc     0x12345678 \n"
    "X12 0x123456789abcdef0 | X28 0x123456789abcdef0 | stval    0x12345678 \n"
    "X13 0x123456789abcdef0 | X29 0x123456789abcdef0 | satp     0x12345678 \n"
    "X14 0x123456789abcdef0 | X30 0x123456789abcdef0 | mcycle   0x12345678 \n"
    "X15 0x123456789abcdef0 | X31 0x123456789abcdef0 | minstret 0x12345678 \n";

   boost::asio::write(socket, boost::asio::buffer(block));
}
// ---------------------------------------------------------------------
// INFO - Variables
// ---------------------------------------------------------------------
void Server::info_variables(tcp::socket &socket, ArgsType &args)
{
  unimplemented_command("info",socket,args);
//  string response = "Info "+tq(args[0]);
//  boost::asio::write(socket, boost::asio::buffer(response));
}
// =====================================================================
// RRR
// =====================================================================
// ---------------------------------------------------------------------
// RESTART - server control
// ---------------------------------------------------------------------
void Server::handle_restart(tcp::socket &socket, ArgsType &args)
{
    std::cout << "-I: Resuming server task..." << std::endl;
    busy_flag = true;

    // If the stop_flag is set, the busy task has stopped, so restart it
    if (stop_flag) {
      stop_flag = false;  // Reset the stop flag to resume the task
      std::thread busy_thread(&Server::busy_task, this);
      busy_thread.detach();  // Detach the thread so it runs independently
    }
    boost::asio::write(socket, boost::asio::buffer("<1>"));
}
// =====================================================================
// SSS
// =====================================================================
// SET
// ---------------------------------------------------------------------
void Server::handle_set(tcp::socket &socket, ArgsType &args) {
    if (args.size() != 2) {
        std::string error_msg = "-I: Usage: set <variable> <value>\n";
        boost::asio::write(socket, boost::asio::buffer(error_msg));
        return;
    }

    std::string var_name = args[0];
    std::string value = args[1];
    std::string response;

    auto it = variables.find(var_name);
    if (it == variables.end()) {
        response = "-E: Unknown variable name: " + var_name + "\n";
    } else {
        try {
            std::visit([&](auto& var) {
                using T = std::decay_t<decltype(var)>;
                if constexpr (std::is_same_v<T, std::string>) {
                    // Set string value
                    var = value;
                    response = "<\"" + var + "\">\n";
                } else if constexpr (std::is_same_v<T, int64_t>) {
                    // Convert and set int value
                    var = std::stoll(value);
                    response = "<" + std::to_string(var) + ">\n";
                } else if constexpr (std::is_same_v<T, uint64_t>) {
                    // Convert and set unsigned int
                    var = std::stoull(value);
                    //var = static_cast<uint64_t>(std::stoul(value));
                    response = "<" + std::to_string(var) + ">\n";
                } else if constexpr (std::is_same_v<T, bool>) {
                    if (value == "true") {
                        var = true;
                        response = "<true>\n";
                    } else if (value == "false") {
                        var = false;
                        response = "<false>\n";
                    } else {
                        response = "-E: Invalid value type, expected bool.\n";
                    }
                } else if constexpr (std::is_same_v<T, float>) {
                    // Convert and set float
                    var = std::stof(value);
                    response = "<" + std::to_string(var) + ">\n";
                } else if constexpr (std::is_same_v<T, double>) {
                    // Convert and set double
                    var = std::stod(value);
                    response = "<" + std::to_string(var) + ">\n";
                }
            }, it->second);
        } catch (std::invalid_argument&) {
            response = "-E: Invalid value type.\n";
        } catch (std::out_of_range&) {
            response = "-E: Value out of range.\n";
        }
    }

    boost::asio::write(socket, boost::asio::buffer(response));
}
// ---------------------------------------------------------------------
// SHOW
// ---------------------------------------------------------------------
void Server::handle_show(tcp::socket &socket, ArgsType &args) {
    if (args.size() != 1) {
        string error_msg = "Usage: show <variable>\n";
        boost::asio::write(socket, boost::asio::buffer(error_msg));
        return;
    }

    string var_name = args[0];
    string response;

    if (var_name == "string_var") {
        response = "string_var: " + string_var + "\n";
    }
    else if (var_name == "int_var") {
        response = "int_var: " + ::to_string(int_var) + "\n";
    }
    else if (var_name == "bool_var") {
        response = "bool_var: " + string(bool_var ? "true" : "false") + "\n";
    }
    else {
        response = "-E: Unknown variable name: " + var_name + "\n";
    }

    boost::asio::write(socket, boost::asio::buffer(response));
}
// ---------------------------------------------------------------------
// SHUTDOWN - server control
// ---------------------------------------------------------------------
void Server::handle_shutdown(tcp::socket &socket, ArgsType &args)
{
    std::cout << "-I: Shutting down server..." << std::endl;
    shutdown_flag = true;
    boost::asio::write(socket, boost::asio::buffer("<1>"));
}
// ---------------------------------------------------------------------
// STOP - server control
// ---------------------------------------------------------------------
void Server::handle_stop(tcp::socket &socket, ArgsType &args)
{
    std::cout << "-I: Stopping server task..." << std::endl;
    busy_flag = false;
    boost::asio::write(socket, boost::asio::buffer("<1>"));
}