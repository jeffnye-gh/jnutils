// --------------------------------------------------------------------------
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
// ---------------------------------------------------------------------------
#include "test.h"
#include "options.h"
#include "msg.h"

Options *Options::instance = 0;
std::shared_ptr<Options> opts(Options::getInstance());

Msg *Msg::instance = 0;
std::unique_ptr<Msg> msg(Msg::getInstance());

int main(int ac,char **av)
{
  msg->setWho("test");

  opts->setup_options(ac,av);

  Test test(2,3);
  return 0;
}
