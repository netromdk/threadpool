#include <iostream>
using std::cout;
using std::endl;

#include "ThreadPool.h"

void func() {
  for (int j = 0; j < 10; j++) {
    // Do stuff..
  }
}

int main() {
  int amount = 10;

  cout << "Enqueuing " << amount << " tasks.." << endl;
  ThreadPool<void> pool;
  for (int i = 0; i < amount; i++) {
    // Add as lvalue for testing.
    ThreadPool<void>::Task f(func);
    pool.queueTask(f);
  }

  cout << "Processing.." << endl;
  pool.process();

  cout << "Done" << endl;
  return 0;
}
