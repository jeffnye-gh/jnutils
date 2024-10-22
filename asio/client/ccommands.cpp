// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "client.h"
#include "common.h"
#include <thread>
#include <chrono>
#include <string>
#include <fstream>

using boost::asio::ip::tcp;
using namespace std;
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Client::badCommandSyntax(const string &cmd,ArgsType &args)
{
  cout<<"-E: incorrect syntax for command "<<tq(cmd)<<endl;
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Client::handle_cset(ArgsType &args)
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
void Client::handle_csrc(tcp::socket& socket,ArgsType &args)
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
bool Client::send_command(tcp::socket& socket, const string& command) {
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
    cout << "\n" << data << endl;

    if (string(data).substr(0, 3) == "-E:") {
      return false;  // Indicates an error response
    }

    return true;
  } catch (exception& e) {
    cout << "-E: Error sending command: " << e.what() << endl;
    return false;
  }
}
