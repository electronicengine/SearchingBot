#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <chrono>


class ThreadPool
{

    std::condition_variable Condition_;
    std::vector<std::thread> Workers_;
    std::queue<std::function<void()>> Tasks_;
    std::mutex lock;

public:
    ThreadPool();


    void setWorkerSize(int Size);

    template<class F, class ...ARG>
    auto pushWork(F && Func, ARG &&... Args)
    -> std::future<typename std::result_of<F(ARG...)>::type>
    {
        using return_type = typename std::result_of<F(ARG...)>::type;

        auto packaged_func = std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<F>(Func), std::forward<ARG>(Args)...)
                    );

        Tasks_.emplace([=]{(*packaged_func)(); });

        std::future<return_type> response = packaged_func->get_future();

        Condition_.notify_one();

        return response;

    }

};




#endif // THREADPOOL_H
