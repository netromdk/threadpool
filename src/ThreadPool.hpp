#ifdef THREAD_POOL_H

#include <thread>

template <typename RetType>
ThreadPool<RetType>::ThreadPool(int threads) {
  if (threads == -1) {
    threads = std::thread::hardware_concurrency();
  }
  if (threads <= 0) {
    threads = 1;
  }
  this->threads = threads;
}

template <typename RetType>
void ThreadPool<RetType>::queueTask(const Task &task) {
  tasks.push(task);
}

template <typename RetType>
void ThreadPool<RetType>::queueTask(Task &&task) {
  tasks.emplace(std::move(task));
}

template <typename RetType>
void ThreadPool<RetType>::process() {
  while (!tasks.empty()) {
    auto taskAmount = tasks.size();
    int amount = (threads > taskAmount ? taskAmount : threads);

    for (int i = 0; i < amount; i++) {
      auto task = tasks.front();
      tasks.pop();

      auto future = std::async(std::launch::async, [=]{
          return task();
        });
      futuresPending.emplace_back(std::move(future));
    }

    for (auto &future : futuresPending) {
      future.wait();
      futuresDone.emplace_back(std::move(future));
    }

    futuresPending.clear();
  }
}

#endif // THREAD_POOL_H
