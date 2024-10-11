// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "server.h"
#include <string>
using namespace std;
// ---------------------------------------------------------------------
// SSS
// ---------------------------------------------------------------------
void Server::send_block(tcp::socket& socket) {
  string block =
    "X0  0x0000000000000000 | X16 0x0000000000000000 | mstatus  0x12345678 \n"
    "X1  0x0000234987234000 | X17 0x0000234987234000 | mcause   0x12345678 \n"
    "X2  0xaaabdbdbd3434340 | X18 0xaaabdbdbd3434340 | mepc     0x12345678 \n"
    "X3  0x123456789abcdef0 | X19 0x123456789abcdef0 | mtval    0x12345678 \n"
    "X4  0x123456789abcdef0 | X20 0x123456789abcdef0 | mie      0x12345678 \n"
    "X5  0x123456789abcdef0 | X21 0x123456789abcdef0 | mscratch 0x12345678 \n"
    "X6  0x123456789abcdef0 | X22 0x123456789abcdef0 | mstatus  0x12345678 \n"
    "X7  0x123456789abcdef0 | X23 0x123456789abcdef0 | mtime    0x12345678 \n"
    "X8  0x123456789abcdef0 | X24 0x123456789abcdef0 | mtimecmp 0x12345678 \n"
    "X9  0x123456789abcdef0 | X25 0x123456789abcdef0 | sstatus  0x12345678 \n"
    "X10 0x123456789abcdef0 | X26 0x123456789abcdef0 | scause   0x12345678 \n"
    "X11 0x123456789abcdef0 | X27 0x123456789abcdef0 | sepc     0x12345678 \n"
    "X12 0x123456789abcdef0 | X28 0x123456789abcdef0 | stval    0x12345678 \n"
    "X13 0x123456789abcdef0 | X29 0x123456789abcdef0 | satp     0x12345678 \n"
    "X14 0x123456789abcdef0 | X30 0x123456789abcdef0 | mcycle   0x12345678 \n"
    "X15 0x123456789abcdef0 | X31 0x123456789abcdef0 | minstret 0x12345678 \n";

   boost::asio::write(socket, boost::asio::buffer(block));
}

