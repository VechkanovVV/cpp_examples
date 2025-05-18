#include "thread_pool.hpp"

#include <iostream>
#include <thread>

int main() {
    tp::ThreadPool pool{4};

    size_t shared_counter = 0;

    for (size_t i = 0; i < 100500; ++i) {
        pool.add_task([&]() {
            shared_counter++;
        });
    }
    
    pool.wait();

    std::cout << shared_counter << std::endl;

    pool.stop();
}