// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
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
