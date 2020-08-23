#include <iostream>
#include <thread>
#include <memory>

#include "ui_thread.h"

int main()
{
  std::shared_ptr<std::thread> t = std::make_shared<std::thread>(ui_thread);
  if (t->joinable())
  { 
    t->join();
  }

  getchar();

  return 0;
}