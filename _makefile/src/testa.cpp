#include "testa.h"
#include <iostream>
Testa::Testa(int _invar) 
  : invar(_invar)
{
  std::cout<<"Testa CTOR: "<<invar<<std::endl;
}
