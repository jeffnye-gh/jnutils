#include "testb.h"
#include <iostream>
Testb::Testb(int _invar) 
  : invar(_invar)
{
  std::cout<<"Testb CTOR: "<<invar<<std::endl;
}

Testb::~Testb() {}
