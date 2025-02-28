#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <string>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <test_time>" << std::endl;
        return 1;
    }

    int test_time = std::stoi(argv[1]);
    const int HUGE_BUFFER_SIZE = 1024 * 1024 * 1024; // 1 GB
    volatile char* buffer = new char[HUGE_BUFFER_SIZE];
    
    int thread_count = std::jthread::hardware_concurrency();
    std::vector<std::jthread> threads;
    std::vector<std::atomic_int64_t> data_movement(thread_count);
    std::vector<std::atomic_bool> set_info_flags(thread_count);


    auto thread_f = [&](std::stop_token stop_token, int id) {
        int i = (HUGE_BUFFER_SIZE / thread_count) * id;
        int64_t data_move = 0;
        int step = 1024 * 1024 * 64;
        while (!stop_token.stop_requested()) {
            memset((void*)(buffer + i), i, step);
            i+=step;
            i %= HUGE_BUFFER_SIZE;
            data_move += step;
            if (set_info_flags[id]) {
                data_movement[id] += data_move;
                data_move = 0;
                set_info_flags[id] = false;
            }   
        }
    };

    for (int i = 0; i < thread_count; i++) {
        threads.emplace_back(thread_f, i);
        data_movement[i] = 0;
        set_info_flags[i] = false;
    }

    int64_t total_data_movement = 0;
    for (int i = 0; i < test_time * 2; i++) {
        if (i % 2 && i > 1) {
            
            total_data_movement = 0;
            for (int i = 0; i < thread_count; i++) {
                total_data_movement += data_movement[i];
            }
#ifdef __cpp_lib_format
            std::cout << std::format(
                "Total   data movement  (so far) : {:>10.2f} MB\n"
                "Average data movement per second: {:>10.2f} MB\n\n", 
                (float)total_data_movement / (1024 * 1024), 
                (float)total_data_movement / (1024 * 1024) / ((i - 1) / 2));
#else
            std::cout << "Total   data movement  (so far) : " << (float)total_data_movement / (1024 * 1024) << " MB\n"
                "Average data movement per second: " << (float)total_data_movement / (1024 * 1024) / ((i - 1) / 2) << " MB\n\n";   
#endif    
        }
        else for (int j = 0; j < thread_count; j++) {
            set_info_flags[j] = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    for (int i = 0; i < thread_count; i++) {
        threads[i].request_stop();
    }

    for (int i = 0; i < thread_count; i++) {
        threads[i].join();
    }

    total_data_movement = 0;
    for (int i = 0; i < thread_count; i++) {
        total_data_movement += data_movement[i];
    }
        
    delete[] buffer;
    return 0;
}