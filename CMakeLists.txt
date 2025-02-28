cmake_minimum_required(VERSION 3.10)

project(BandwidthSaturationTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -D_GLIBCXX_USE_STD_FORMAT")
add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 23)


# Add the main executable as a test
enable_testing()
add_test(NAME MainTest COMMAND main 10)