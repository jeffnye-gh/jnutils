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
// -------------------------------------------------------------------
void Jndbg::initVariablesFields()
{
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initDisassemblyFields()
{
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initCommandFields()
{
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Jndbg::initStatusBarFields()
{
}



