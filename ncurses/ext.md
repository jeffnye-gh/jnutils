# GCC options
https://gcc.gnu.org/onlinedocs/gcc/RISC-V-Options.html

U64 | S64 |   Label
M   | M   |   g   General-purpose computing base extension, ‘g’ will expand to 
    |     |       i         2.0, 2.1  Base integer extension.
    |     |       m         2.0       Integer multiplication and division extension.
    |     |       a         2.0, 2.1  Atomic extension.
    |     |       f         2.0, 2.2  Single-precision floating-point extension.
    |     |       d         2.0, 2.2  Double-precision floating-point extension.
    |     |       zicsr     2.0       Control and status register access extension.
 -  |  M  |       zifencei  2.0        Instruction-fetch fence extension.
    |     |   
n/a | n/a |   e            2.0  Reduced base integer
 M  |  M  |   c            2.0  Compressed
 -  |  M  |   h            1.0  Hypervisor
 M  |  M  |   v            1.0  Vector
 M  |  M  |   zicond       1.0  Integer conditional operations
 M  |  M  |   za64rs       1.0  Reservation set size of 64 bytes.
    |     |   za128rs      1.0  Reservation set size of 128 bytes.
 M  |  M  |   zawrs        1.0  Wait-on-reservation-set
    |     |   zba          1.0  Address calculation
 M  |  M  |   zbb          1.0  Basic bit manipulation
 M  |  M  |   zbc          1.0  Carry-less multiplication
 M  |  M  |   zbs          1.0  Single-bit operation
    |     |   zfinx        1.0  Single-precision floating-point in integer registers
    |     |   zdinx        1.0  Double-precision floating-point in integer registers
    |     |   zhinx        1.0  Half-precision floating-point in integer registers
    |     |   zhinxmin     1.0  Minimal half-precision floating-point in integer regs
    |     |   zbkb         1.0  Cryptography bit-manipulation
    |     |   zbkc         1.0  Cryptography carry-less multiply
    |     |   zbkx         1.0  Cryptography crossbar permutation
    |     |   zkne         1.0  AES Encryption
    |     |   zknd         1.0  AES Decryption
    |     |   zknh         1.0  Hash function
 -  |  e  |   zkr          1.0  Entropy source
    |     |   zksed        1.0  SM4 block cipher
    |     |   zksh         1.0  SM3 hash function
 M  |  M  |   zkt          1.0  Data independent execution latency
    |     |   zk           1.0  Standard scalar cryptography
    |     |         zkn    1.0  NIST algorithm suite
    |     |         zks    1.0  ShangMi algorithm suite
 M  |  M  |   zihintntl    1.0  Non-temporal locality hints
 M  |  M  |   zihintpause  1.0  Pause hint
 M  |  M  |   zicboz       1.0  Cache-block zero
 M  |  M  |   zicbom       1.0  Cache-block management
 M  |  M  |   zicbop       1.0  Cache-block prefetch
 M  |  M  |   zic64b       1.0  Cache block size isf 64 bytes.
 M  |  M  |   ziccamoa     1.0  Main memory supports all atomics in A.
 M  |  M  |   ziccif       1.0  Main memory supports instr fetch with atomicity requirement.
 M  |  M  |   zicclsm      1.0  Main memory supports misaligned loads/stores.
 M  |  M  |   ziccrse      1.0  Main memory supports forward progress on LR/SC sequences.
 M  |  M  |   zicntr       2.0  Standard extension for base counters and timers.
 M  |  M  |   zihpm        2.0  Standard extension for hardware performance counters.
    |     |   ztso         1.0  Total store ordering extension.
    |     |   zve32x       1.0  Vector extensions for embedded processors.
    |     |   zve32f       1.0  Vector extensions for embedded processors.
    |     |   zve64x       1.0  Vector extensions for embedded processors.
    |     |   zve64f       1.0  Vector extensions for embedded processors.
    |     |   zve64d       1.0  Vector extensions for embedded processors.
 M  |  M  |   zvl32b       1.0  Minimum vector length standard extensions
 M  |  M  |   zvl64b       1.0  Minimum vector length standard extensions
 M  |  M  |   zvl128b      1.0  Minimum vector length standard extensions
    |     |   zvl256b      1.0  Minimum vector length standard extensions
    |     |   zvl512b      1.0  Minimum vector length standard extensions
    |     |   zvl1024b     1.0  Minimum vector length standard extensions
    |     |   zvl2048b     1.0  Minimum vector length standard extensions
    |     |   zvl4096b     1.0  Minimum vector length standard extensions
 M  |  M  |   zvbb         1.0  Vector basic bit-manipulation extension.
    |     |   zvknha       1.0  Vector SHA-2 secure hash extension.
    |     |   zvkn         1.0  Vector NIST Algorithm Suite extension, ‘zvkn’ expands to 
    |     |       zvkned       1.0  Vector AES block cipher extension.
    |     |       zvknhb       1.0  Vector SHA-2 secure hash extension.
    |     |       zvkb         1.0  Vector cryptography bit-manipulation extension.
 M  |  M  |       zvkt         1.0  Vector data independent execution latency extension.
    |     |   zvknc        1.0  Vector NIST Algor Suite with carryless mul ext, expands to 
    |     |       ‘zvkn’ see above
 d  |  d  |        zvbc    1.0  Vector carryless multiplication extension.
 l  |  l  |   zvkng  1.0  Vector NIST Algorithm Suite with GCM extension, ‘zvkng’ will expand to ‘zvkn’ and ‘zvkg’.
    |     |       ‘zvkn’ see above
    |     |       zvkg         1.0  Vector GCM/GMAC extension.

    |     |   zvks  1.0  Vector ShangMi algorithm suite extension, ‘zvks’ will expand to ‘zvksed’, ‘zvksh’, ‘zvkb’ and ‘zvkt’.
    |     |       zvksed       1.0  Vector SM4 Block Cipher extension.
    |     |       zvksh        1.0  Vector SM3 Secure Hash extension.

    |     |   zvksc  1.0  Vector ShangMi algorithm suite with carryless multiplication extension, ‘zvksc’ will expand to ‘zvks’ and ‘zvbc’.
 l  |  l  |   zvksg  1.0  Vector ShangMi algorithm suite with GCM extension, ‘zvksg’ will expand to ‘zvks’ and ‘zvkg’.
 e  |  e  |   zfh  1.0  Half-precision floating-point extension.
 M  |  M  |   zfhmin  1.0  Minimal half-precision floating-point extension.
 e  |  e  |   zvfh  1.0  Vector half-precision floating-point extension.
 M  |  M  |   zvfhmin  1.0  Vector minimal half-precision floating-point extension.
 e  |  e  |   zvfbfmin  1.0  Vector BF16 converts extension.
 M  |  M  |   zfa  1.0  Additional floating-point extension.
    |     |   zmmul  1.0  Integer multiplication extension.
    |     |   zca  1.0  Integer compressed instruction extension.
    |     |   zcf  1.0  Compressed single-precision floating point loads and stores extension.
    |     |   zcd  1.0  Compressed double-precision floating point loads and stores extension.
 M  |  M  |   zcb  1.0  Simple compressed instruction extension.
    |     |   zce  1.0  Compressed instruction extensions for embedded processors.
    |     |   zcmp  1.0  Compressed push pop extension.
    |     |   zcmt  1.0  Table jump instruction extension.
    |     |   smaia  1.0  Advanced interrupt architecture extension.
    |     |   smepmp  1.0  PMP Enhancements for memory access and execution prevention on Machine mode.
    |     |   smstateen  1.0  State enable extension.
    |     |   ssaia  1.0  Advanced interrupt architecture extension for supervisor-mode.
 -  |  M  |   sscofpmf  1.0  Count overflow & filtering extension.
 -  |  M  |   ssstateen  1.0  State-enable extension for supervisor-mode.
 -  |  M  |   sstc  1.0  Supervisor-mode timer interrupts extension.
 -  |  M  |   svinval  1.0  Fine-grained address-translation cache invalidation extension.
 -  |  M  |   svnapot  1.0  NAPOT translation contiguity extension.
 -  |  M  |   svpbmt  1.0  Page-based memory types extension.
