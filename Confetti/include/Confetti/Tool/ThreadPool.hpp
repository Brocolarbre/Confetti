#pragma once

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

namespace cft
{
    class ThreadPool
    {
    private:
        std::vector<std::thread> m_workers;
        std::queue<std::function<void()>> m_tasks;

        std::mutex m_mutex;
        std::condition_variable m_condition;
        bool m_stop;

    public:
        ThreadPool(std::size_t threadCount = std::thread::hardware_concurrency());
        ThreadPool(const ThreadPool& threadPool) = delete;
        ThreadPool(ThreadPool&& threadPool) = delete;
        ~ThreadPool();

        ThreadPool& operator=(const ThreadPool& threadPool) = delete;
        ThreadPool& operator=(ThreadPool&& threadPool) = delete;

        std::size_t threadCount() const;

        template<typename F, typename... Args>
        std::future<std::invoke_result_t<F, Args...>> enqueue(F&& f, Args&&... args)
        {
            auto task = std::make_shared<std::packaged_task<std::invoke_result_t<F, Args...>()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
            std::future<std::invoke_result_t<F, Args...>> future = task->get_future();

            {
                std::lock_guard<std::mutex> lock(m_mutex);

                if (m_stop)
                    throw std::runtime_error("Called enqueue on a stopped thread pool");

                m_tasks.emplace([task]() { (*task)(); });
            }

            m_condition.notify_one();
            return future;
        }
    };
}