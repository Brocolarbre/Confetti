#include "Confetti/Tool/ThreadPool.hpp"

namespace cft
{
    ThreadPool::ThreadPool(std::size_t threadCount) :
        m_workers(),
        m_tasks(),
        m_mutex(),
        m_condition(),
        m_stop(false)
    {
        if (threadCount == 0)
            threadCount = 1;

        m_workers.reserve(threadCount);

        for (std::size_t i = 0; i < threadCount; ++i)
        {
            m_workers.emplace_back([this]() {
                while (true)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(m_mutex);

                        m_condition.wait(lock, [this]() {
                            return m_stop || !m_tasks.empty();
                        });

                        if (m_stop && m_tasks.empty())
                            return;

                        task = std::move(m_tasks.front());
                        m_tasks.pop();
                    }

                    task();
                }
            });
        }
    }

    ThreadPool::~ThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_stop = true;
        }

        m_condition.notify_all();

        for (std::thread& worker : m_workers)
        {
            if (worker.joinable())
                worker.join();
        }
    }

    std::size_t ThreadPool::threadCount() const
    {
        return m_workers.size();
    }
}