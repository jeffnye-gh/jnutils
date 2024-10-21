#pragma once

#include <cstdint>
#include <iomanip>

typedef uint8_t UINT8_T;
//typedef uint32_t UINT8_T;

#define NUM_CPUS 1

//#define TAGE_PC_SHIFT 5
#define PC_SHIFT 5

#define CAST(N)  static_cast<uint32_t>(N)
#define HEX(W,N) std::hex<<std::setw(W)<<std::setfill('0')<<N
#define DEC      std::dec

