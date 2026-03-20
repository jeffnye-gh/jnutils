
#include <cstdint>
volatile uint32_t glbl=0;

int main(int,char**)
{
  while(1) { glbl += 1;  }
  return 0;
}
