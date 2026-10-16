#include "queue.hpp"
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

namespace d2fb::jobs {

class WorkerPool {
public:
    explicit WorkerPool(size_t n) {
        for (size_t i = 0; i < n; ++i)
            workers_.emplace_back([this] { run(); });
    }
    ~WorkerPool() {
        { std::lock_guard lk(mu_); stop_ = true; }
        cv_.notify_all();
        for (auto& t : workers_) t.join();
    }
    void submit(std::function<void()> fn) {
        { std::lock_guard lk(mu_); queue_.push_back(std::move(fn)); }
        cv_.notify_one();
    }
private:
    void run() {
        for (;;) {
            std::function<void()> job;
            {
                std::unique_lock lk(mu_);
                cv_.wait(lk, [&] { return stop_ || !queue_.empty(); });
                if (stop_ && queue_.empty()) return;
                job = std::move(queue_.front());
                queue_.erase(queue_.begin());
            }
            job();
        }
    }
    std::vector<std::thread> workers_;
    std::vector<std::function<void()>> queue_;
    std::mutex mu_;
    std::condition_variable cv_;
    bool stop_{false};
};

} // namespace d2fb::jobs