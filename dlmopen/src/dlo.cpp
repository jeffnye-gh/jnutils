#include "protos.h"
#include <iostream>
using namespace std;

int glbl = 99;

void hack0(void)  { cout<<"HERE hack0"<<endl; return; }
int  hack1(void)  { cout<<"HERE hack1"<<endl; return glbl; }
int  hack2(int a) { cout<<"HERE hack2 got "<<a <<endl; return a+1; }
int  hack3(int ac,char **av) { cout<<"HERE hack3 got "<<ac<<endl; return ac+2; }

void hack4(int ac)            {
  cout<<"HERE hack4 glbl was "<<glbl<<endl;
  glbl = ac;
  cout<<"HERE hack4 glbl is now "<<glbl<<endl;
}
