#pragma once
#include <string>
#include <iostream>
#include <fstream>

struct Msg
{
  //verbose=3 enables emsg, wmsg and imsg
  Msg(std::string _who="",int _verbose=3)
    : w(_who+": "),
      verbose(_verbose)
  {}

  void setWho(std::string _w) {  w = _w+": "; }

  void mmsg(std::string p,std::string m)
    { std::cout<<p<<w<<m<<std::endl; }
  
  void dmsg(std::string m="",int v=4)
    { if(v<=verbose) mmsg("-D: ",m); }

  void emsg(std::string m="",int v=1)
    { if(v<=verbose) mmsg("-E: ",m); }

  void imsg(std::string m="",int v=3)
    { if(v<=verbose) mmsg("-I: ",m); }

  void wmsg(std::string m="",int v=2)
    { if(v<=verbose) mmsg("-W: ",m); }

  void mmsg(std::ostream& o,std::string p,std::string m)
    { o<<p<<w<<m<<std::endl; }

  //dmsg should be v level 4
  void dmsg(std::ostream& o,std::string m="",int v=4)
    { mmsg(o,"-D: ",m); }

  void emsg(std::ostream& o,std::string m="",int v=1)
    { mmsg(o,"-E: ",m); }
  void imsg(std::ostream& o,std::string m="",int v=3)
    { mmsg(o,"-I: ",m); }
  void wmsg(std::ostream& o,std::string m="",int v=2)
    { mmsg(o,"-W: ",m); }

  void  msg(std::string m)
    { std::cout<<m<<std::endl;  }

  std::string w;
  // ----------------------------------------------------------------
  // verbose 0 - silent
  //         1 - errors
  //         2 - errors,warnings
  //         3 - errors,warnings,info
  //         >= 4 - errors,warnings,info,debug4
  //              - debug messages can be a various levels, debugN
  // ----------------------------------------------------------------
  int  verbose;
};
