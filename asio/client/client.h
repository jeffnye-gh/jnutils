// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
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

