#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>
#include <string>

struct Client
{
  Client() {}

  uint32_t connect();

  void setPrompt(std::string s) { prompt = s; }
  std::string prompt{"client> "};
};

