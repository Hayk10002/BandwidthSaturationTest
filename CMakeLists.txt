cmake_minimum_required(VERSION 3.10)

project(MiddleInsertion)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 23)

# Add the main executable as a test
enable_testing()
add_test(NAME MainTest COMMAND main 10000 1000)