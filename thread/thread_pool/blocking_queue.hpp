#pragma once

#include <cstdlib>
#include <deque>
#include <mutex>
#include <cassert>
#include <thread>
#include <condition_variable>
#include <iostream>


namespace tp {

    template <typename T>
    class BlockingQueue {
        public:
            void put(T value) {
                std::lock_guard guard(mtx_);
                buffer_.push_back(std::move(value));
                not_emty_queue_.notify_one();
            }

            T take() {
                std::unique_lock lock(mtx_);
                while (buffer_.empty()) {
                    not_emty_queue_.wait(lock);
                }

                return take_locked();

            }
        private:
            T take_locked() {
                assert(!buffer_.empty());

                T front{std::move(buffer_.front())};
                buffer_.pop_front();
                return front;
            }

        private:
            std::deque<T> buffer_;
            std::mutex mtx_;
            std::condition_variable not_emty_queue_;

    };
}