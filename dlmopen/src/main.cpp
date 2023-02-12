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
#include <dlfcn.h>
#include <string>
#include <iostream>
using namespace std;

bool run_once(string msg,void *dl,char** av,int a,int b,int c)
{
  cout<<endl<<"HERE "<<msg<<endl;

  typedef void (vv_t) (void);
  typedef vv_t* vv_p;

  typedef int (iv_t) (void);
  typedef iv_t* iv_p;

  typedef int (ii_t) (int);
  typedef ii_t* ii_p;

  typedef int (iic_t) (int,char**);
  typedef iic_t* iic_p;

  typedef int (vi_t) (int);
  typedef vi_t* vi_p;

  vv_p func_hack0  = (vv_p)  dlsym(dl,"_Z5hack0v");
  iv_p func_hack1  = (iv_p)  dlsym(dl, "_Z5hack1v");
  ii_p func_hack2  = (ii_p)  dlsym(dl, "_Z5hack2i");
  iic_p func_hack3 = (iic_p) dlsym(dl, "_Z5hack3iPPc");
  vi_p func_hack4  = (vi_p)  dlsym(dl, "_Z5hack4i");

  if(!func_hack0) { cout<<"could not find hack0"<<endl; return false; }
  if(!func_hack1) { cout<<"could not find hack1"<<endl; return false; }
  if(!func_hack2) { cout<<"could not find hack2"<<endl; return false; }
  if(!func_hack3) { cout<<"could not find hack3"<<endl; return false; }
  if(!func_hack4) { cout<<"could not find hack4"<<endl; return false; }

  func_hack0();
  int h1 = func_hack1();
  int h2  = func_hack2(a);
  func_hack3(b,av);

  cout<<msg<<" "<<"HERE hack1 ret was "<<h1<<endl;
  cout<<msg<<" "<<"HERE hack2 ret was "<<h2<<endl;
  func_hack4(c);
  h1 = func_hack1();
  cout<<msg<<" "<<"HERE s1_hack1 ret was "<<h1<<endl<<endl;
  return true;
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
int main(int ac,char **av)
{
  void *dlo1 = dlmopen(LM_ID_NEWLM,"./lib/libdlo.so", RTLD_LOCAL | RTLD_LAZY);
  void *dlo2 = dlmopen(LM_ID_NEWLM,"./lib/libdlo.so", RTLD_LOCAL | RTLD_LAZY);
  void *dlo3 = dlmopen(LM_ID_NEWLM,"./lib/libdlo.so", RTLD_LOCAL | RTLD_LAZY);

  if(!dlo1) {
    cout<<"dlopen error "<<dlerror()<<endl;
    exit(1);
  }

  if(!dlo2) {
    cout<<"dlopen error "<<dlerror()<<endl;
    exit(1);
  }

  if(!dlo3) {
    cout<<"dlopen error "<<dlerror()<<endl;
    exit(1);
  }

  if(!run_once("DLO_1",dlo1,av,4,6,123)) return 1;
  if(!run_once("DLO_2",dlo2,av,7,8,321)) return 1;
  if(!run_once("DLO_3",dlo3,av,9,2,101)) return 1;

  return 0;
}
