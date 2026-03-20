CC_BASE="/usr/local/riscv32-embecosm-ubuntu2204-gcc13.2.0"
CC="$CC_BASE/bin/riscv32-unknown-elf-g++"
GDB="$CC_BASE/bin/riscv32-unknown-elf-gdb"
OBJDUMP="$CC_BASE/bin/riscv32-unknown-elf-objdump"

CFLAGS="-march=rv64gc_zba_zbb_zbc_zbs -mabi=lp64d"
$CC $CFLAGS main.cpp -o main.riscv

$GDB main.riscv
