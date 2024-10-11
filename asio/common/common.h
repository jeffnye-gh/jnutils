#pragma once
#include <cstdint>
#include <string>

struct Comms
{
  static inline std::string hostip  = "127.0.0.1";
  static inline uint32_t    tcpport = 12345;
  static std::string get_comms() { return hostip+":"+std::to_string(tcpport); }
};
