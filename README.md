ThreadPool
==========

ThreadPool is a templated, include-only library written entirely in C++11. No linking required.

It works by simply adding a number of tasks to be computed and then processing them. By default it will use as many software threads as there are hardware threads on the system.

Usage
=====
The pool is easy to use: add some tasks and process them:

```cpp
#include "ThreadPool.h"

ThreadPool<void> pool;
for (int i = 0; i < 10; i++) {
  pool.queueTask([]{
      /* do work */
    });
 }

// Blocks until all tasks have been processed.
pool.process();
```

If the tasks yield a result then those can easily be used afterwards:
```cpp
#include "ThreadPool.h"

ThreadPool<int> pool;
for (int i = 0; i < 10; i++) {
  pool.queueTask([]{
      /* do work */
      return /* result */;
    });
 }

pool.process();

for (auto &future : pool.getFutures()) {
  auto value = future.get();
  /* use results */
}
```

In some cases you don't want it to be blocking so you can have it invoke a callback on completion:
```cpp
#include "ThreadPool.h"

ThreadPool<void> pool;
for (int i = 0; i < 10; i++) {
  pool.queueTask([]{
      /* do work */
    });
 }

pool.process([]{
    /* called when done with all tasks */
  });
  
// Continues with program while tasks are being processed..
```

Tests
=====

Requires a C++11 compliant compiler (GCC 4.8+, Clang 3.3+ etc.) and CMake 3+.

While the library is include-only there are a few test programs which can be compiled and tried out:

1. Extract source and go into the diretory.
2. `mkdir build`
3. `cd build`
4. `cmake ..`
5. `make`

This will produce the following test programs in the "bin" folder:
* intpool - Tests a simple pool with integer results.
* voidpool - Tests a simple pool with no results.
* sum - Asynchronally sums all numbers of a vector.
* funcpool - Tests a simple pool with lvalue funcs.
* callback - Tests non-blocking process() with a callback.
