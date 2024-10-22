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

  string response = strResp(false,"Too few arguments for command "+tq(cmd));
  boost::asio::write(socket, boost::asio::buffer(response));
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Server::unknown_subcommand(string base,tcp::socket &socket, ArgsType &args)
{
  string response = strResp(false,"Unknown subcommand "+tq(args[0])
                                          +" for command "+tq(base));
  boost::asio::write(socket, boost::asio::buffer(response));
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
void Server::unimplemented_command(string base,tcp::socket &socket, ArgsType &args)
{
  string response = strResp(false,"Command "
                            +tq(base+" "+args[0])+" has not been implemented");
  boost::asio::write(socket, boost::asio::buffer(response));
}
// =====================================================================
// HHH
// =====================================================================

void Server::handle_help(tcp::socket &socket, ArgsType &args)
{
  string response = strResp(true,"Help message");
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
  } else if(args[0] == "b" || args[0] == "bp" || args[0] == "breakpoints") {
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
// Fake data for testing
// ---------------------------------------------------------------------
void Server::info_regs(tcp::socket &socket, ArgsType&) {
    std::string response = "-I:INFO_REGS:NVP:X0:0x0000000000000000:"
                           "X1:0x0000234987234000:"
                           "X2:0xaaabdbdbd3434340:"
                           "X3:0x123456789abcdef0:"
                           "X4:0x123456789abcdef0:"
                           "X5:0x123456789abcdef0:"
                           "X6:0x123456789abcdef0:"
                           "X7:0x123456789abcdef0:"
                           "X8:0x123456789abcdef0:"
                           "X9:0x123456789abcdef0:"
                           "X10:0x123456789abcdef0:"
                           "X11:0x123456789abcdef0:"
                           "X12:0x123456789abcdef0:"
                           "X13:0x123456789abcdef0:"
                           "X14:0x123456789abcdef0:"
                           "X15:0x123456789abcdef0:"
                           "mstatus:0x12345678:"
                           "mcause:0x12345678:"
                           "mepc:0x12345678:"
                           "mtval:0x12345678:"
                           "mie:0x12345678:"
                           "mscratch:0x12345678:"
                           "mtime:0x12345678:"
                           "mtimecmp:0x12345678:"
                           "sstatus:0x12345678:"
                           "scause:0x12345678:"
                           "sepc:0x12345678:"
                           "stval:0x12345678:"
                           "satp:0x12345678:"
                           "mcycle:0x12345678:"
                           "minstret:0x12345678";

    boost::asio::write(socket, boost::asio::buffer(response));
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
    boost::asio::write(socket, boost::asio::buffer(retCode(true)));
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
        response = strResp(false,"Unknown variable name: " + var_name);
    } else {
        try {
            std::visit([&](auto& var) {
                using T = std::decay_t<decltype(var)>;
                if constexpr (std::is_same_v<T, std::string>) {
                    // Set string value
                    var = value;
                    response = strResp(true,"<\"" + var + "\">");
                } else if constexpr (std::is_same_v<T, int64_t>) {
                    // Convert and set int value
                    var = std::stoll(value);
                    response = strResp(true,"<" + std::to_string(var) + ">");
                } else if constexpr (std::is_same_v<T, uint64_t>) {
                    // Convert and set unsigned int
                    var = std::stoull(value);
                    //var = static_cast<uint64_t>(std::stoul(value));
                    response = strResp(true,"<" + std::to_string(var) + ">");
                } else if constexpr (std::is_same_v<T, bool>) {
                    if (value == "true") {
                        var = true;
                        response = strResp(true,"<true>");
                    } else if (value == "false") {
                        var = false;
                        response = strResp(true,"<false>");
                    } else {
                        response
                          = strResp(false,"Invalid value type, expected bool");
                    }
                } else if constexpr (std::is_same_v<T, float>) {
                    // Convert and set float
                    var = std::stof(value);
                    response = strResp(true,"<" + std::to_string(var) + ">");
                } else if constexpr (std::is_same_v<T, double>) {
                    // Convert and set double
                    var = std::stod(value);
                    response = strResp(true,"<" + std::to_string(var) + ">");
                }
            }, it->second);
        } catch (std::invalid_argument&) {
            response = strResp(false,"Invalid value type");
        } catch (std::out_of_range&) {
            response = strResp(false,"Value out of range");
        }
    }

    boost::asio::write(socket, boost::asio::buffer(response));
}
// ---------------------------------------------------------------------
// SHOW
// ---------------------------------------------------------------------
void Server::handle_show(tcp::socket &socket, ArgsType &args) {
  if (args.size() != 1) {
      string error_msg = strResp(false,"Usage: show <variable>");
      boost::asio::write(socket, boost::asio::buffer(error_msg));
      return;
  }

  string var_name = args[0];
  string response;

  if (var_name == "string_var") {
    response = strResp(true,"string_var: " + string_var);
  } else if (var_name == "int_var") {
    response = strResp(true,"int_var: " + ::to_string(int_var));
  } else if (var_name == "bool_var") {
    response = strResp(true,"bool_var: " + string(bool_var ? "true" : "false"));
  } else {
    response = strResp(false,"Unknown variable name: " + var_name);
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
    boost::asio::write(socket, boost::asio::buffer(retCode(true)));
}
// ---------------------------------------------------------------------
// STOP - server control
// ---------------------------------------------------------------------
void Server::handle_stop(tcp::socket &socket, ArgsType &args)
{
    std::cout << "-I: Stopping server task..." << std::endl;
    busy_flag = false;
    boost::asio::write(socket, boost::asio::buffer(retCode(true)));
}
