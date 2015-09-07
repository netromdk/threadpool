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

  for (int i = 0; i < 3; i++) {
    pool.queueTask([i]{
        std::this_thread::sleep_for(std::chrono::milliseconds(500 * (i+1)));
        cout << "this was added after process started" << endl;
      });
  }

  // Only one processing invocation can be live at any one time. A mutex
  // protects against it. Because of the callback to the above process() it will
  // return immediately, but it will still hold the lock so this call will wait.
  pool.process();

  return 0;

  // When pool is to be destroyed it will join its thread if joinable. In other
  // words, it will wait if need be instead of prematurely stopping the
  // asynchronous computations.
}
