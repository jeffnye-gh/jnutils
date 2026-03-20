#pragma once

namespace ucmds
{
  using boost::asio::ip::tcp;
  using ArgsType = const std::vector<std::string>;
  using CommandHandler = std::function<void(tcp::socket&,ArgsType&)>;
  using CommandMap     = std::map<std::string, CommandHandler>;
}
