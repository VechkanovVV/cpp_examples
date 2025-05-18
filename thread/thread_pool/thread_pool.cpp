#include "thread_pool.hpp"

namespace tp {
    ThreadPool::ThreadPool(size_t n) {
        has_finished_.store(false);
        start_worker_threads(n);
    }

    ThreadPool::~ThreadPool() {
        stop();
    }

    void ThreadPool::add_task(Task task) {
        tasks_.put(task);
    }

    void ThreadPool::start_worker_threads(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            workers_.emplace_back([this](){
                worker_routine();
            });
        }
    }

    void ThreadPool::worker_routine() {
        while (!has_finished_.load()) {
            auto task = tasks_.take();
            task();
        }
    }

    void ThreadPool::wait() {
        
    }

    void ThreadPool::stop() {
        has_finished_.store(true);
        for(auto& worker : workers_) {
            if(worker.joinable()) worker.join();
        }
    }
}