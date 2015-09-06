#include <chrono>
#include <iostream>
using std::cout;
using std::endl;

#include "ThreadPool.h"

int main() {
  ThreadPool<void> pool;
  pool.queueTask([]{
      cout << "computing.." << endl;
      for (int i = 0; i < 10; i++) {
        cout << i << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
      }
      cout << "done.." << endl;
    });

  cout << "before" << endl;
  pool.process([]{
      cout << "done callback!" << endl;
    });
  cout << "after" << endl;

  return 0;

  // When pool is to be destroyed it will join its thread if joinable. In other
  // words, it will wait if need be instead of prematurely stopping the
  // asynchronous computations.
}
