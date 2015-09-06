#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <queue>
#include <thread>
#include <vector>
#include <future>
#include <functional>

template <typename RetType>
class ThreadPool {
public:
  using Task = std::function<RetType()>;

private:
  using TaskQueue = std::queue<Task>;
  using FutVec = std::vector<std::future<RetType>>;

public:
  ThreadPool(int threads = std::thread::hardware_concurrency());

  void queueTask(Task task);
  void process();

  int getThreadCount() const { return threads; }
  FutVec &getFutures() { return futuresDone; }

private:
  int threads;
  TaskQueue tasks;
  FutVec futuresDone, futuresPending;
};

#include "ThreadPool.cpp"

#endif // THREAD_POOL_H
