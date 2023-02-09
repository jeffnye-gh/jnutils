// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#pragma once
#include "mshell.h"
#include <vector>
#include <string>

#define ARG std::vector<std::string>&
struct Mstest
{
  Mstest(Mshell &_ms);
  ~Mstest() {}

  enum CMDS {
    M_CMD_HANDLER = Mshell::USER_TYPE,

    M_SRC_FILE,
    M_SET_VAR,
    M_SHOW_VAR,
    M_SHOW_VARS,
    M_SHOW_SETTINGS,
    M_RUN,
    M_RESET,
    M_RESPOND_CLIENT,
    M_FORCE_FAIL,
    LAST_CMD
  };

  // ---------------------------------------------------------------------
  bool dispatch(std::vector<std::string>&);
  bool appCmd(uint32_t,std::vector<std::string>&);
  bool undef(ARG);

  bool forceFail(ARG);
  bool releaseNotes(ARG);
  bool reset(ARG);
  bool run(ARG);
  bool setVar(ARG);
  bool showSettings(ARG);
  bool showVar(ARG);
  bool showVars(ARG);
  bool srcFile(ARG);
  bool version(ARG);

  bool respondToClient(ARG);

  Mshell &ms;
};
#undef ARG
