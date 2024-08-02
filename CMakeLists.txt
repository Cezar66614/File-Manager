cmake_minimum_required(VERSION 3.0.0)
project(File-Manager VERSION 0.1.0)

set(
  PROG_SRCS

  src/main.c
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${PROG_SRCS})
target_link_libraries(${PROJECT_NAME} pthread)
