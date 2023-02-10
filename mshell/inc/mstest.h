// ----------------------------------------------------------------------------
// This file is part of jnutils, made public 2023, (c) Jeff Nye
//
// jnutils is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// jnutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with jnutils; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
// ----------------------------------------------------------------------------
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
