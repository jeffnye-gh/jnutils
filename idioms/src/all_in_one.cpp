#include "msg.h"
#include "boost/algorithm/string.hpp"

#include <iostream>
#include <fstream>
using namespace std;

Msg *Msg::instance = 0;
std::unique_ptr<Msg> msg(Msg::getInstance());

int main(int,char**)
{
  string fn = "myfile.txt";
  ifstream in(fn.c_str());

  if(!in.is_open()) {
    msg->emsg("Could not open file "+fn);
  }

  std::string line;
  while (std::getline(in, line)) {
    vector<string> vec;
     boost::split(vec,line,
                  boost::is_any_of(" \t\n\r"),boost::token_compress_on);
     for(size_t i=0;i<vec.size();++i) {
       string sep = i==0 ? "" : "|";
       cout<<sep<<vec[i];
     }
     cout<<endl;
  }

  msg->imsg("Complete");
  return 0;
}

