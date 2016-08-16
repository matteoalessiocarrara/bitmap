cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

add_executable(${PROJECT_NAME} test.c)
target_link_libraries(${PROJECT_NAME} m)
