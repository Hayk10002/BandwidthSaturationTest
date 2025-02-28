# BandwidthSaturationTest

## Table of Contents
- [Introduction](#introduction)
- [Build and Run](#build-and-run)
- [Possible Output](#possible-output)
- [How does this work](#how-does-this-work)

## Introduction
The purpose of this project is to maximally stress the memory bandwidth and calculate its speed.

## Build and Run
To clone and run this project, you'll need [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. From your command line:

```bash
# Clone this repository
$ git clone https://github.com/Hayk10002/BandwidthSaturationTest

# Go into the repository
$ cd BandwidthSaturationTest

# Generate the build files
$ cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

# Build the project
$ cmake --build build --config Release

# Then, run the executable generated in the `build` directory with the number of seconds to run the test.
$ your/path/to/exe/main.exe {The number of seconds to run the test}
# example - .../main.exe 10
```

## Possible Output
(for 10 seconds)

```
Total   data movement  (so far) :   14016.00 MB
Average data movement per second:   14016.00 MB

Total   data movement  (so far) :   28096.00 MB
Average data movement per second:   14048.00 MB

Total   data movement  (so far) :   41728.00 MB
Average data movement per second:   13909.33 MB

Total   data movement  (so far) :   55168.00 MB
Average data movement per second:   13792.00 MB

Total   data movement  (so far) :   69952.00 MB
Average data movement per second:   13990.40 MB

Total   data movement  (so far) :   85248.00 MB
Average data movement per second:   14208.00 MB

Total   data movement  (so far) :  100672.00 MB
Average data movement per second:   14381.71 MB

Total   data movement  (so far) :  116416.00 MB
Average data movement per second:   14552.00 MB

Total   data movement  (so far) :  131712.00 MB
Average data movement per second:   14634.67 MB
```

## How does this work
The project measures memory bandwidth by continuously writing to a large buffer using multiple threads. Each thread starts writing to a distinct portion of the buffer to but isn't restricted to it. The total amount of data written is tracked and reported periodically.

The code creates a buffer of 1 GB. Each thread writes to the buffer in a loop, updating the total data written. The main thread periodically collects and prints the total data written by all threads, providing an estimate of the memory bandwidth.

The results show the total data movement and the average data movement per second, giving insights into the memory bandwidth performance of the system.
