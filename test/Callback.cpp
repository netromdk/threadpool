#include <thread>
#include <chrono>
#include <iostream>
using std::cout;
using std::endl;

#include "ThreadPool.h"

void f() {
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
      exit(0);
    });
  cout << "after" << endl;

  // Simulate the program continuing while the thread pool is computing.
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main() {
  std::thread t(f);
  t.join();
  return 0;
}
