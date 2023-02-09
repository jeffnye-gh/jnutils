// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#include "test.h"
#include "options.h"
#include "msg.h"

Options *Options::instance = 0;
std::shared_ptr<Options> opts(Options::getInstance());

Msg *Msg::instance = 0;
std::unique_ptr<Msg> msg(Msg::getInstance());

int main(int ac,char **av)
{
  msg->setWho("test");

  opts->setup_options(ac,av);

  Test test(2,3);
  return 0;
}
