cmake_minimum_required(VERSION 3.23)
project(automata)

set(CMAKE_CXX_STANDARD 14)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
