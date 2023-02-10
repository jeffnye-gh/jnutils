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
#pragma once
#include <boost/program_options.hpp>
namespace po = boost::program_options;

struct Options
{ 
  // ----------------------------------------------------------------
  // singleton 
  // ----------------------------------------------------------------
  static Options* getInstance() {
    if(!instance) instance = new Options();
    return instance;
  }
  // ----------------------------------------------------------------
  // support methods
  // ----------------------------------------------------------------
  void build_options(po::options_description&,
                     po::options_description&,
                     po::positional_options_description&);

  bool check_options(po::variables_map&,
                     po::options_description&,
                     po::options_description&,
                     po::positional_options_description&,
                     bool);

  void setup_options(int,char**);

  void usage(po::options_description&,
             po::positional_options_description&);

  void version();
  void query_options();
  // ----------------------------------------------------------------
  // example options
  // ----------------------------------------------------------------
  std::string ini_file; //not implemented yet

  std::vector<std::string> multi_option;

  bool bool_flag;
  bool _query_options; //also bool flag

  int  plain_option;

  int  hidden_one;
  int  hidden_two;

  std::string positional_option;
  // ----------------------------------------------------------------
  // ----------------------------------------------------------------
  bool notify_error;
  po::variables_map vm;

  // more singleton 
  static Options *instance;
private:
  // ----------------------------------------------------------------
  // more singleton 
  // ----------------------------------------------------------------
  Options() {} //default
  Options(const Options&) = delete; //copy
  Options(Options&&)      = delete; //move
  Options& operator=(const Options&) = delete; //assignment
};

extern std::shared_ptr<Options> opts;
