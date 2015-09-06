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
