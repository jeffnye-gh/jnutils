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
// -----------------------------------------------------------------------------
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

struct Msg
{
  static Msg* getInstance() {
    if(!instance) instance = new Msg;
    return instance;
  }
 
 ~Msg() {} //dtor

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

  // ----------------------------------------------------------------
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

  // ----------------------------------------------------------------
  std::string tq(std::string s) { return "'"+s+"'"; }
  std::string w;
  // ----------------------------------------------------------------
  // verbose 0 - silent
  //         1 - errors
  //         2 - errors,warnings
  //         3 - errors,warnings,info
  //         >= 4 - errors,warnings,info,debug4
  //              - debug messages can be a various levels, debugN
  // ----------------------------------------------------------------
  int  verbose{3};
  static Msg *instance;

 private:
  Msg() { w = ""; verbose = 3; }
  // ------------------------------------------------------------------- 
  //  Msg(std::string _who="",int _verbose=3)
  //    : w(_who+": "),
  //      verbose(_verbose)
  //  {}
  // ------------------------------------------------------------------- 
  Msg(const Msg&) = delete; //copy
  Msg(Msg&&) = delete; //move
  Msg& operator=(const Msg&) = delete; //assign

};

extern std::unique_ptr <Msg> msg;

