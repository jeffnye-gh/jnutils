// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

struct Client
{
    using ArgsType = const std::vector<std::string>;

    Client() {}

    uint32_t connect();

    void setPrompt(const std::string s) { prompt = s; }
    bool isCommand(const std::string &);
    void badCommandSyntax(const std::string &,ArgsType&);

private:

    std::string tq(const std::string s) { return "'"+s+"'"; }
    void handle_cset(ArgsType&);
    void handle_csrc(tcp::socket&,ArgsType&);
    bool send_command(tcp::socket& socket,const std::string& cmd);

    bool stop_on_error;
    std::string prompt{"asio> "};
};
