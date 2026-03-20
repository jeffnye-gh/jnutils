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
#include "msg.h"
#include "options.h"
#include <iostream>
using namespace std;
// --------------------------------------------------------------------
// Build the option set and check the options
// --------------------------------------------------------------------
void Options::setup_options(int ac,char **av)
{
  notify_error = false;

  po::options_description visibleOpts(
   "\nBoost Option Example\n "
   "Usage:: gdbserver [--help|-h|--version|-v] | [std options]");

  po::options_description stdOpts("Standard options");
  build_options(stdOpts);

  try {
    po::store(po::parse_command_line(ac, av, allOpts), vm);
  } catch(boost::program_options::error& e) {
    msg->msg("");
    msg->emsg("Command line option parsing failed");
    msg->emsg("What: " + string(e.what()));
    usage(stdOpts);
    exit(1);
  }

  po::notify(vm);
  if(!check_options(vm,stdOpts)) exit(1);
}
// --------------------------------------------------------------------
// Construct the std, hidden and positional option descriptions
// --------------------------------------------------------------------
void Options::build_options(po::options_description &stdOpts)
{
  stdOpts.add_options()
    ("help,h", "...")

    ("version,v", "report version and exit")

    ("multi", po::value<vector<string> >(&multi_option),
     "Example multiple instance option")

    ("bool_flag", po::bool_switch(&bool_flag),
     "Example flag option")

    ("plain,p", po::value<int>(&plain_option),
     "Integer option with short and long form")
  ;

}
// --------------------------------------------------------------------
// Check sanity on the options, handle --help, --version
// --------------------------------------------------------------------
bool Options::check_options(po::variables_map &vm,
                            po::options_description &stdOpts)
{
  if(vm.count("help"))    { usage(visibleOpts,posOpts); return false; }
  if(vm.count("version")) { version(); return false; }

  if(!bool_flag) {
    msg->emsg("bool_flag must be set");
    return false;
  }

  return true;
}
// --------------------------------------------------------------------
// --------------------------------------------------------------------
void Options::usage(po::options_description &opts)
{
  cout<<opts<<endl;
}
// --------------------------------------------------------------------
void Options::version()
{
  msg->imsg("Gdb RSP Server");
  msg->imsg("Version: v"+std::string(VERSION));
  msg->imsg("Slack jeff w/any questions");
  msg->imsg("");
}
