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
    using ArgsType = std::vector<std::string>;

    Client() {}

    uint32_t connect();
    void setPrompt(const std::string s) { prompt = s; }

private:

    std::string tq(const std::string s) { return "'"+s+"'"; }
    void handle_cset(const ArgsType&);
    void handle_csrc(tcp::socket&,const ArgsType&);

    bool parse_response(const std::string &status_code,
                        const std::string &command_id,
                        const std::string &data_type,
                        const ArgsType &payload,
                        const std::string &strPayload);

    void handle_info_regs(const std::string &,const ArgsType &);
    void handle_general_cmd(const std::string &,const std::string &);
    void handle_ret_code(const std::string &,const std::string &);

    bool send_command(tcp::socket& socket,const std::string& cmd);
    void badCommandSyntax(const std::string &,const ArgsType&);
    bool isCommand(const std::string &);

    bool stop_on_error;
    std::string prompt{"asio> "};
};
