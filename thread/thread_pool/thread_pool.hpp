#pragma once

#include "blocking_queue.hpp"
#include "task.hpp"

#include <cstddef>
#include <thread>
#include <vector>
#include <atomic>

namespace tp
{
    class ThreadPool {
        public:
            explicit ThreadPool (size_t amount);
            ~ThreadPool();

            ThreadPool(const ThreadPool&) = delete;
            ThreadPool operator= (const ThreadPool&) = delete;

            void add_task(Task task);

            void wait();

            void stop();

        private:
            void start_worker_threads(size_t n);
            void worker_routine();

        private:
            std::vector<std::thread> workers_;
            BlockingQueue<Task> tasks_;
            std::atomic<bool> has_finished_;
            
    };
    
} // namespace tp
