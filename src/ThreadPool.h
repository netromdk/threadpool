#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <queue>
#include <thread>
#include <vector>
#include <future>
#include <functional>

template <typename RetType> ///< Return type of tasks.
class ThreadPool {
public:
  using Task = std::function<RetType()>;
  using Callback = std::function<void()>;

private:
  using TaskQueue = std::queue<Task>;
  using FutVec = std::vector<std::future<RetType>>;

public:
  /// -1 threads means to use as many threads as there are hardware threads on
  /// the system.
  ThreadPool(int threads = -1);

  void queueTask(const Task &task);
  void queueTask(Task &&task);

  /// Process all enqueued tasks.
  /** If no completion callback is defined then it
      will block until done, otherwise it returns immediately and the callback
      will be invoked when done. */
  void process(Callback callback = Callback());

  int getThreadCount() const { return threads; }
  FutVec &getFutures() { return futuresDone; }

private:
  void _process();

  int threads;
  std::thread thread;
  TaskQueue tasks;
  FutVec futuresDone, futuresPending;
};

#include "ThreadPool.hpp"

#endif // THREAD_POOL_H
