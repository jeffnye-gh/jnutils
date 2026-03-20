// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#pragma once
#include <cstdint>
#include <string>

struct Comms
{
  static inline std::string hostip  = "127.0.0.1";
  static inline uint32_t    tcpport = 12345;
  static inline uint32_t    retry_wait = 5;
  static std::string get_ip()    { return hostip; }
  static std::string get_port()  { return std::to_string(tcpport); }
  static std::string get_comms() { return hostip+":"+std::to_string(tcpport); }
};
