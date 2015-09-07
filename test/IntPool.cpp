#include <iostream>
using std::cout;
using std::endl;

#include "ThreadPool.h"

int main() {
  int amount = 10;

  cout << "Enqueuing " << amount << " tasks.." << endl;
  ThreadPool<int> pool;
  for (int i = 0; i < amount; i++) {
    pool.queueTask([i]{ return i; });
  }

  cout << "Processing.." << endl;
  pool.process();

  for (auto &future : pool.getFutures()) {
    cout << "Result: " << future.get() << endl;
  }

  cout << "Enqueuing " << amount << " tasks.." << endl;
  for (int i = 0; i < amount; i++) {
    pool.queueTask([i]{ return i; });
  }

  cout << "Processing.." << endl;
  pool.process();

  for (auto &future : pool.getFutures()) {
    cout << "Result: " << future.get() << endl;
  }
  return 0;
}
