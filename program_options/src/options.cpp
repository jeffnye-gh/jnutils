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
   "Usage:: test [--help|-h|--version|-v] {[options] {positional_option}}");

  po::options_description allOpts("All options");
  po::options_description stdOpts("Standard options");
  po::options_description hiddenOpts("Hidden options");

  //not implemented  po::options_description iniOpts("Config file options");
  po::positional_options_description posOpts;

  build_options(stdOpts,hiddenOpts,posOpts);

  visibleOpts.add(stdOpts);
  allOpts.add(stdOpts).add(hiddenOpts);

  try {
    po::store(
      po::command_line_parser(ac, av)
          .options(allOpts).positional(posOpts).run(),vm
    );

    //Without positional option po::parse_command_line can be used
    //po::store(po::parse_command_line(ac, av, allOpts), vm);

  } catch(boost::program_options::error& e) {
    msg->msg("");
    msg->emsg("1st pass command line option parsing failed");
    msg->emsg("What: " + string(e.what()));
    usage(stdOpts,posOpts);
    exit(1);
  }

  po::notify(vm);
  if(!check_options(vm,allOpts,visibleOpts,posOpts,true)) exit(1);
}
// --------------------------------------------------------------------
// Construct the std, hidden and positional option descriptions
// --------------------------------------------------------------------
void Options::build_options(po::options_description &stdOpts,
                            po::options_description &hiddenOpts,
                            po::positional_options_description &posOpts)
{
  stdOpts.add_options()
    ("help,h", "...")

    ("version,v", "report version and exit")

    ("query_options",po::bool_switch(&_query_options)->default_value(false),
     "report option settings and exit")

    ("ini",   po::value<string>(&ini_file), 
     "Path to json configuration file")

    ("multi", po::value<vector<string> >(&multi_option),
     "Example multiple instance option")

    ("bool_flag", po::bool_switch(&bool_flag),
     "Example flag option")

    ("plain,p", po::value<int>(&plain_option),
     "Integer option with short and long form")
  ;

  hiddenOpts.add_options()
    ("hidden_one", po::value<int>(&hidden_one),
     "Hidden option #1, accepted but not listed in usage")

    ("hidden_two", po::value<int>(&hidden_two),
     "Hidden option #2, accepted but not listed in usage")

    ("positional_option", po::value<string>(&positional_option),
     "Positional option example")
  ;

  posOpts.add("positional_option",-1); 
}
// --------------------------------------------------------------------
// Check sanity on the options, handle --help, --version
// --------------------------------------------------------------------
bool Options::check_options(po::variables_map &vm,
                            po::options_description &allOpts,
                            po::options_description &visibleOpts,
                            po::positional_options_description &posOpts,
                            bool firstPass)
{
  if(firstPass) {
    if(vm.count("help"))    { usage(visibleOpts,posOpts); return false; }
    if(vm.count("version")) { version(); return false; }
  } else {
    //insert option checks for 2nd pass only, usually ini file
    //not implemented yet
  }

  if(_query_options) { query_options(); return true; }

  if(!bool_flag) {
    msg->emsg("bool_flag must be set");
    return false;
  }

  return true;
}
// --------------------------------------------------------------------
// --------------------------------------------------------------------
void Options::usage(po::options_description &opts,
                    po::positional_options_description &posOpts)
{
  msg->imsg("BEG Options::usage()");
  cout<<opts<<endl;
  //cout<<posOpts<<endl;
  msg->imsg("END Options::usage()");
}
// --------------------------------------------------------------------
void Options::version()
{
  msg->imsg("BEG Options::version()");
  msg->imsg("");
  msg->imsg("Boost program_option example");
  msg->imsg("Version: v"+std::string(VERSION));
  msg->imsg("Slack jeff w/any questions");
  msg->imsg("");
  msg->imsg("END Options::version()");
}
// --------------------------------------------------------------------
// --------------------------------------------------------------------
void Options::query_options()
{
  msg->imsg("BEG Options::query_options()");
  msg->imsg("ini_file         : "+ini_file);
  msg->imsg("bool_flag        : "+string(bool_flag ? "True" : "False"));
  msg->imsg("_query_options   : "+string(_query_options ? "True" : "False"));
  msg->imsg("plain_options    : "+::to_string(plain_option));
  msg->imsg("hidden_one       : "+::to_string(hidden_one));
  msg->imsg("hidden_two       : "+::to_string(hidden_two));
  msg->imsg("positional_option: "+positional_option);

  msg->imsg("Multi-option");
  for(size_t i=0;i<multi_option.size();++i) {
    msg->imsg( "  #"+::to_string(i)+ " : "+multi_option[i]);
  }

  msg->imsg("END Options::query_options()");
}
