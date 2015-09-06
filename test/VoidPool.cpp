#include <iostream>
using std::cout;
using std::endl;

#include "ThreadPool.h"

int main() {
  int amount = 10;

  cout << "Enqueuing " << amount << " tasks.." << endl;
  ThreadPool<void> pool;
  for (int i = 0; i < amount; i++) {
    pool.queueTask([i]{
        for (int j = 0; j < i; j++) {
          // Do stuff..
        }
      });
  }

  cout << "Processing.." << endl;
  pool.process();

  cout << "Done" << endl;
  return 0;
}
