#include <chrono>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

#include "ThreadPool.h"

int main() {
  int elms = 99999999;
  int value= 7;
  cout << "Filling data vector with " << elms << " " << value << "s.. ";
  cout.flush();
  std::vector<long> vec(elms, value);
  cout << "Done!" << endl;

  ThreadPool<long> pool;
  auto size = vec.size();
  auto threads = pool.getThreadCount();
  auto amount = size / threads;

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < threads; i++) {
    auto pos = i * amount;
    if (i == threads - 1) {
      amount = size - pos;
    }
    pool.queueTask([pos, amount, &vec]{
        decltype(pos) res = 0, end = pos + amount;
        for (auto j = pos; j < end; j++) {
          res += vec[j];
        }
        return res;
      });
  }

  cout << "Processing.. ";
  cout.flush();
  pool.process();
  cout << "Done!" << endl;

  long res = 0;
  for (auto &future : pool.getFutures()) {
    res += future.get();
  }

  auto dur = std::chrono::high_resolution_clock::now() - start;
  auto ms = std::chrono::duration<double, std::milli>(dur).count();
  cout << "Result: " << res << endl;
  cout << "Took " << ms << " ms." << endl << endl;
  return 0;
}
