include_directories(${threadpool_SOURCE_DIR}/src)

add_executable(
  intpool
  IntPool.cpp
  )

add_executable(
  voidpool
  VoidPool.cpp
  )

add_executable(
  sum
  Sum.cpp
  )

add_executable(
  funcpool
  FuncPool.cpp
  )

add_executable(
  callback
  Callback.cpp
  )

add_executable(
  callback2
  Callback2.cpp
  )
