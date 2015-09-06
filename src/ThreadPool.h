#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <queue>
#include <vector>
#include <future>
#include <functional>

template <typename RetType> ///< Return type of tasks.
class ThreadPool {
public:
  using Task = std::function<RetType()>;

private:
  using TaskQueue = std::queue<Task>;
  using FutVec = std::vector<std::future<RetType>>;

public:
  /// -1 threads means to use as many threads as there are hardware threads on
  /// the system.
  ThreadPool(int threads = -1);

  void queueTask(const Task &task);
  void queueTask(Task &&task);

  void process();

  int getThreadCount() const { return threads; }
  FutVec &getFutures() { return futuresDone; }

private:
  int threads;
  TaskQueue tasks;
  FutVec futuresDone, futuresPending;
};

#include "ThreadPool.hpp"

#endif // THREAD_POOL_H
