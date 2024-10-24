// -------------------------------------------------------------------------
//  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
//  See LICENSE in the root directory.
// -------------------------------------------------------------------------
#include "jndbg.h"
#include <vector>

using namespace std;
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initFields()
{
  initXregFields();
  initCsrFields();
  initVariablesFields();
  initWatchpointFields();
  initBreakpointFields();
  initDisassemblyFields();
  initCallStackFields();
  initCommandFields();
  initStatusBarFields();
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initXregFields()
{
  for(size_t i=0;i<32;++i) {

    XregFieldInfo fi(64);

    fi.set_uninit();
    fi.set_modified(false);

    string label_key("X"+::to_string(i));
    string label = label_key;
    label.resize(4,' ');
    fi.label = label;

    fi.label_x  = i<16 ? XregFieldInfo::XREG_0_Lbl_x
                       : XregFieldInfo::XREG_1_Lbl_x;

    fi.data_x   = i<16 ? XregFieldInfo::XREG_0_Dat_x
                       : XregFieldInfo::XREG_1_Dat_x;

    fi.active_x = i<16 ? XregFieldInfo::XREG_0_Act_x
                       : XregFieldInfo::XREG_1_Act_x;

    size_t idx = i < 16 ? i : i-16;

    uint32_t y = XregFieldInfo::XREG_y+(idx);
    fi.label_y  = y;
    fi.data_y   = y;
    fi.active_y = y;

    xregs.insert(make_pair(label_key,fi));
  }
}

// -------------------------------------------------------------------
//CSRs are a bit messy to initialize
// -------------------------------------------------------------------
void Jndbg::initCsrFields()
{
  string zero_reset = "0x0000000000000000";
  uint32_t ypos = CsrFieldInfo::CSR_y;

  vector<string> names = {
    "ustatus",
    "utvec",
    "ucause",
    "uttval",
    "mstatus",
    "misa",
    "medeleg",
    "mideleg",
    "mie",
    "mtvec",
    "mscratch",
    "mepc",
    "mcause",
    "mtval",
    "mip",
    "mcycle",
    "mvendorid",
    "marchid",
    "mimplid",
    "mhartid"
  };

  uint32_t cnt = 0;
  for(auto &n : names) {

    bool even = !(cnt&0x1);

    uint32_t l_x = even ? CsrFieldInfo::CSR_0_Lbl_x
                        : CsrFieldInfo::CSR_1_Lbl_x;
    uint32_t d_x = even ? CsrFieldInfo::CSR_0_Dat_x
                        : CsrFieldInfo::CSR_1_Dat_x;
    uint32_t a_x = even ? CsrFieldInfo::CSR_0_Act_x
                        : CsrFieldInfo::CSR_1_Act_x;

    CsrFieldInfo fi(64,false,false,
                    n, zero_reset, "-",
                    l_x,ypos,
                    d_x,ypos,
                    a_x,ypos);

    csrs.insert(make_pair(n,fi));

    ypos += cnt&0x1;
    ++cnt;
  }
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initBreakpointFields()
{
  string uninit64 = "0x----------------";

  for(size_t i=0;i<16;++i) {
    string label(::to_string(i));
    label.resize(2,' ');

    uint32_t ypos = BreakPointFieldInfo::BP_y+i;

    BreakPointFieldInfo fi(64,true,false,
                           label,uninit64," ",
                           BreakPointFieldInfo::BP_0_Lbl_x,ypos,
                           BreakPointFieldInfo::BP_0_Enb_x,ypos,
                           BreakPointFieldInfo::BP_0_Dat_x,ypos,
                           BreakPointFieldInfo::BP_0_Act_x,ypos,
                           false);
    fi.enable = "-"; //tristate: undefined(-), enabled(E), disabled(D)
    breakpoints.insert(make_pair(i,fi));
  }

}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initWatchpointFields()
{
  string uninit64 = "0x----------------";

  for(size_t i=0;i<16;++i) {
    string label(::to_string(i));
    label.resize(2,' ');

    uint32_t ypos = WatchPointFieldInfo::WP_y+i;

    WatchPointFieldInfo fi(64,true,false,
                           label,uninit64,uninit64," ",
                           WatchPointFieldInfo::WP_0_Lbl_x,ypos,
                           WatchPointFieldInfo::WP_0_Enb_x,ypos,
                           WatchPointFieldInfo::WP_0_Adr_x,ypos,
                           WatchPointFieldInfo::WP_0_Dat_x,ypos,
                           WatchPointFieldInfo::WP_0_Act_x,ypos,
                           false);
    fi.enable = "-"; //tristate: undefined(-), enabled(E), disabled(D)
    watchpoints.insert(make_pair(i,fi));
  }
}

// -------------------------------------------------------------------
const map<string,pair<string,string> > Jndbg::example_variables = {
  { "_mshEcho",              { "bool",     "true"               } },
  { "_my64b_long_name",      { "uint64_t", "0x123456789abcdef0" } },
  { "_my32b_mid_name",       { "uint32_t", "0x12345678"         } },
  { "bitstreamBuffer",       { "uint8_t",  "null"               } },
  { "macroblockWidth",       { "int32_t",  "0x00000010"         } },
  { "quantizationParameter", { "int32_t",  "0x00000024"         } },
  { "profileIdc",            { "int32_t",  "0x00000066"         } },
  { "isCABACEnabled",        { "bool",     "true"               } }
};
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initVariablesFields()
{
  uint32_t ypos = VariablesFieldInfo::Var_y;

  for(auto &[key,val] : example_variables) {

    size_t size = 32;

    if(val.first == "uint8_t" || val.first == "int8_t") {
      size = 8;
    } else if(val.first == "uint64_t" || val.first == "int64_t") {
      size = 64;
    } else if(val.first == "uint128_t" || val.first == "int128_t") {
      size = 128;
    } else if(val.first == "double") {
      size = 64;
    }

    VariablesFieldInfo fi(size, false, false,
                          key, //label
                          val.first, //type
                          val.second, //data
                          "-", //active
                          VariablesFieldInfo::VAR_0_Lbl_x,ypos,
                          VariablesFieldInfo::VAR_0_Typ_x,ypos,
                          VariablesFieldInfo::VAR_0_Dat_x,ypos,
                          VariablesFieldInfo::VAR_0_Act_x,ypos);
    variables.insert(make_pair(ypos,fi));
    ++ypos;
  
  }
}

// -------------------------------------------------------------------
const map<uint32_t,string> Jndbg::example_disassembly = {
{ 0x800040ca,"d9258593      addi  x11, x11, -0x26e" },
{ 0x800040ce,"467d          c.li  x12, 0x1f" },
{ 0x800040d0,"0a9000ef      jal x1, 0x80004978 <memcpy>" },
{ 0x800040d4,"00001517      auipc x10, 0x1" },
{ 0x800040d8,"d4c53983      ld  x19, -0x2b4(x10)" },
{ 0x800040dc,"00001517      auipc x10, 0x1" },
{ 0x800040e0,"d4c53a03      ld  x20, -0x2b4(x10)" },
{ 0x800040e4,"00001517      auipc x10, 0x1" },
{ 0x800040e8,"d4c53503      ld  x10, -0x2b4(x10)" },
{ 0x800040ec,"e9ce          c.sdsp  x19, 0xd0(x2)" }
};

// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initDisassemblyFields()
{
  uint32_t ypos = VariablesFieldInfo::Var_y;

  for(auto &[key,val] : example_disassembly) {
    DisassemblyFieldInfo fi(key,val,
                            DisassemblyFieldInfo::DIS_Lbl_x,ypos,
                            DisassemblyFieldInfo::DIS_Dat_x,ypos);
    ++ypos;
    disassembly.insert(make_pair(key,fi));
  }
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
const map<uint32_t,string> Jndbg::example_callstack = {
{ 0,"0x000100e6 in main () at main.c:15" },
{ 1,"0x000100bc in start () at crt0.S:98" },
{ 2,"0x000100b8 in _start () at crt0.S:94" },
{ 3,"0x00010084 in __libc_start_main () at libc_start.c:72" },
{ 4,"0x0001005c in __start () at entry.S:58" },
{ 5,"0x0000fff0 in __stack_chk_fail () at stack_chk_fail.c:38" },
{ 6,"0x0000ff90 in __call_exitprocs () at exit.c:101" },
{ 7,"0x0000fe70 in _exit () at syscall.c:35" },
{ 8,"0x0000fc50 in __libc_exit_fini () at exit_fini.c:22" },
{ 9,"0x0000fba0 in __terminate_program () at terminate.c:19" }
};
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initCallStackFields()
{
  uint32_t ypos = CallStackFieldInfo::CALL_y;

  for(auto &[key,val] : example_callstack) {
    CallStackFieldInfo fi(key,val,
                            CallStackFieldInfo::CALL_Lbl_x,ypos,
                            CallStackFieldInfo::CALL_Dat_x,ypos);
    ++ypos;
    callstack.insert(make_pair(key,fi));
  }
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
const map<uint32_t,string> Jndbg::example_commands = {
{0, "asio> target sim" },
{1, "    Connected to the target." },
{2, "asio> file my_program.elf" },
{3, "    Reading symbols from my_program.elf...done." },
{4, "asio> break main" },
{5, "    Breakpoint 1 at 0x100e6: file main.c, line 15." },
{6, "asio> run" },
{7, "    Starting program: /path/to/my_program.elf" },
{8, "    Breakpoint 1, main () at main.c:15" }
//{9, "15        int x = 42;" }
};
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initCommandFields()
{
  uint32_t ypos = CommandFieldInfo::CMD_y;

  for(auto &[key,val] : example_commands) {
    CommandFieldInfo fi(key,val,
                        CommandFieldInfo::CMD_Lbl_x,ypos,
                        CommandFieldInfo::CMD_Dat_x,ypos);
    ++ypos;
    command.insert(make_pair(key,fi));
  }
}

// -------------------------------------------------------------------
map<string,string> Jndbg::example_status = {
  {"MSG",  "Connected to server 127.0.0.1:12345"},
  {"FLAGS","HALTED"}
};
// -------------------------------------------------------------------
void Jndbg::initStatusBarFields()
{
  uint32_t ypos = StatusFieldInfo::STAT_y;

  string msg   = example_status["MSG"];
  string flags = example_status["FLAGS"]; 

  StatusFieldInfo fi(msg,flags,
                     StatusFieldInfo::STAT_Msg_x,ypos,
                     StatusFieldInfo::STAT_Flg_x,ypos);
  status.push_back(fi);
}



