// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "client.h"
#include "common.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

#include <thread>
#include <chrono>
#include <string>
#include <fstream>

using boost::asio::ip::tcp;
using namespace std;
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Client::badCommandSyntax(const string &cmd,const ArgsType &args)
{
  cout<<"-E: incorrect syntax for command "<<tq(cmd)<<endl;
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Client::handle_cset(const ArgsType &args)
{
    if(args.size() < 2) {
      badCommandSyntax("cset",args);
    }

    string var_name  = args[0];
    string value = args[1];

    if (var_name == "stop_on_error") {
        if (value == "true") {
            stop_on_error = true;
            cout << "-I: stop_on_error set to true" << endl;
        } else if (value == "false") {
            stop_on_error = false;
            cout << "-I: stop_on_error set to false" << endl;
        } else {
            cout << "-E: Invalid value for stop_on_error. "
                 << "Use true or false." << endl;
        }
    } else {
        cout << "-E: Unknown client setting: " << var_name << endl;
    }
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Client::handle_csrc(tcp::socket& socket,const ArgsType &args)
{

  if(args.size() == 0) {
    badCommandSyntax("csrc",args);
  }

  string file_path = args[0];

  if (file_path.empty()) {
    cout << "-E: No file path specified for csrc." << endl;
    return;
  }

  ifstream file(file_path);
  if (!file.is_open()) {
      cout << "-E: Unable to open file: " << file_path << endl;
      return;
  }

  string line;

  while (getline(file, line)) {

    if(!isCommand(line)) continue;

    if (!send_command(socket, line) && stop_on_error) {
      cout << "-E: Stopping script execution due to error." << endl;
      break;
    }
  }
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
bool Client::send_command(tcp::socket& socket, const std::string& command) {
    try {
        boost::asio::write(socket, boost::asio::buffer(command + "\n"));

        char data[2048];
        boost::system::error_code error;

        size_t length = socket.read_some(boost::asio::buffer(data), error);

        if (error == boost::asio::error::eof) {
            cout << "-E: Server closed connection." << endl;
            return false;
        } else if (error) {
            throw boost::system::system_error(error);
        }

        data[length] = '\0';
        std::string response(data);

        std::vector<std::string> tokens;
        boost::split(tokens, response, boost::is_any_of(":"),
                                       boost::token_compress_on);

        // Check if we have at least 4 tokens for status, 
        // cmd_id, data_type, and the rest of the data
        if (tokens.size() < 4) {
            cout << "-E: Invalid response format from server." << endl;
            cout << "response: "<<response << endl;
            return false;
        }

        size_t start_index = 0;
        string status    = tokens[start_index++];
        string cmd_id    = tokens[start_index++];
        string data_type = tokens[start_index++];
        vector<string> payload(tokens.begin()+start_index,tokens.end());
        string strPayload = boost::algorithm::join(payload,std::string(1,' '));

        // Check for errors
        if (status == "-E") {
            cout << status << ": "<<strPayload << endl;
            return false;
        }

        return parse_response(status,cmd_id,data_type,payload,strPayload);

    } catch (exception& e) {
        cout << "-E: Error sending command: " << e.what() << endl;
        return false;
    }
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
bool Client::parse_response(const string &status,
                            const string &cmd_id,
                            const string &data_type, //not used currently
                            const ArgsType &payload,
                            const string &strPayload)
{
  (void) data_type;

  if(cmd_id == "INFO_REGS") {
    handle_info_regs(status,payload);
  } else if(cmd_id == "G") {
    handle_general_cmd(status,strPayload);
  } else if(cmd_id == "RET") {
    handle_ret_code(status,strPayload);
  } else {
    cout << "-E: Unknown command response from server "<<tq(cmd_id)<<endl;
    return false;
  }
  return true;
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Client::handle_info_regs(const string &status,const ArgsType &data) {
    // TODO: Implement formatting and printing logic here
    cout << status << ": "<<"INFO_REGS data received: " 
         << boost::algorithm::join(data, std::string(1, ':')) 
         << endl;
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Client::handle_general_cmd(const string &status,
                                const string &strPayload)
{
  cout<<status << ": "<<strPayload<<endl;
}
// -------------------------------------------------------------------
// For now handle_ret_code call general cmd
// -------------------------------------------------------------------
void Client::handle_ret_code(const string &status,
                             const string &strPayload)
{
  handle_general_cmd(status,strPayload);
}
