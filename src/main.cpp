#include <iostream>

#include "cosched.hpp"

using namespace cosched;

class Context {
  public:
    int  cnt = 0;
};

Task<Context> grandchild900(Context& )
{
  std::cout << "grandchild900 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(900)};
  std::cout << "grandchild900 woke up; return" << std::endl;
  co_return;
}

Task<Context> grandchild800(Context&)
{
  std::cout << "grandchild800 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(800)};
  std::cout << "grandchild800 woke up; return" << std::endl;
  co_return;
}

Task<Context> grandchild700(Context&)
{
  std::cout << "grandchild700 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(700)};
  std::cout << "grandchild700 woke up; return" << std::endl;
  co_return;
}
Task<Context> grandchild600(Context&)
{
  std::cout << "grandchild600 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(600)};
  std::cout << "grandchild600 woke up; return" << std::endl;
  co_return;
}
Task<Context> grandchild500(Context&)
{
  std::cout << "grandchild500 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(500)};
  std::cout << "grandchild500 woke up; return" << std::endl;
  co_return;
}
Task<Context> grandchild400(Context&)
{
  std::cout << "grandchild400 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(400)};
  std::cout << "grandchild400 woke up; return" << std::endl;
  co_return;
}
Task<Context> grandchild300(Context&)
{
  std::cout << "grandchild300 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(300)};
  std::cout << "grandchild300 woke up; return" << std::endl;
  co_return;
}
Task<Context> grandchild200(Context&)
{
  std::cout << "grandchild200 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(200)};
  std::cout << "grandchild200 woke up; return" << std::endl;
  co_return;
}

Task<Context> grandchild100(Context&)
{
  std::cout << "grandchild100 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(100)};
  std::cout << "grandchild100 woke up; return" << std::endl;
  co_return;
}


Task<Context> grandchild0(Context&)
{
  std::cout << "grandchild0 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(0)};
  std::cout << "grandchild0 woke up; return" << std::endl;
  co_return;
}

Task<Context> grandchild(Context&)
{
  std::cout << "grandchild started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(300)};
  std::cout << "grandchild woke up; return" << std::endl;
  co_await AwaitSpawn{grandchild900, NULL};
  co_await AwaitSpawn{grandchild0, NULL};
  co_await AwaitSpawn{grandchild800, NULL};
  co_await AwaitSpawn{grandchild100, NULL};
  co_await AwaitSpawn{grandchild700, NULL};
  co_await AwaitSpawn{grandchild200, NULL};
  co_await AwaitSpawn{grandchild600, NULL};
  co_await AwaitSpawn{grandchild300, NULL};
  co_await AwaitSpawn{grandchild500, NULL};

  co_return;
}



Task<Context> child1(Context&)
{
  std::cout << "child1 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(100)};
  std::cout << "child1 woke up; return" << std::endl;
  co_return;
}


Task<Context> child2(Context&)
{
  std::cout << "child2 started; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(10)};
  std::cout << "child2 woke up; spawn grandchild" << std::endl;
  co_await AwaitSpawn{grandchild, NULL};
  co_return;
}


Task<Context> comain(Context&)
{
  std::cout << "main start" << std::endl;

  TaskId child1id, child2id;
  std::cout << "main started; spawn child1" << std::endl;
  co_await AwaitSpawn{child1, &child1id};
  std::cout << "main child1 spawned; spawn child2" << std::endl;
  co_await AwaitSpawn{child2, &child2id};
  std::cout << "main child2 spawned; sleep" << std::endl;
  co_await AwaitSleep{K_MSEC(20)};
  std::cout << "main woke up; spawn child2" << std::endl;
  co_await AwaitSpawn{child2, &child2id};
  std::cout << "main spawned child2; join child1" << std::endl;
  co_await AwaitJoin{child1id};
  std::cout << "main joined child1; join child2" << std::endl;
  co_await AwaitJoin{child2id};
  std::cout << "main joined child2; return" << std::endl;
}

int main()
{
  {
    Context ctx;
  Scheduler<Context> sched(comain, ctx);
  for  (int i = 0; !sched.done(); i++) {
    //cout << "poll {}", i);
    sched.Poll();
    k_sleep(K_MSEC(1));
  }
  }

}
