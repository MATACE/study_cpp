#include <iostream>

#include "my_future.hpp"

int main(int argc, char const *argv[])
{
    // Normal async task.
    AsyncTask async_task;
    int a = 3;
    int b = 4;
    int c = 0;

    // The async is run a async_task point p->add() in the current thread.
    auto f1 = std::async(&AsyncTask::Add, &async_task, a, b, std::ref(c));

    // The async is run a async_task copy new object new_async_task.del() in the current thread.
    auto f2 = std::async(&AsyncTask::Del, async_task, a, b, std::ref(c));

    // The async is run a async_task copy new object new_async_task() in the current thread.
    auto f3 = std::async(AsyncTask(), a, b, std::ref(c));

    // The async is run the async_task async_task object async_task() in the current thread.
    auto f4 = std::async(std::ref(async_task), a, b, std::ref(c));

    // The async is run a async_task copy new object new_async_task() in create a new thread.
    auto f5 = std::async(std::launch::async, AsyncTask(), a, b, std::ref(c));

    // f5.get();
    f5.wait();
    std::cout << c << std::endl;

    // The async is run the async_task async_task object async_task() in the current thread.
    auto f6 = std::async(std::launch::deferred, AsyncTask(), a, b, std::ref(c));
    
    // The async is run the async_task async_task object async_task() will have two choice.
    auto f7 = std::async(std::launch::async | std::launch::deferred, AsyncTask(), a, b, std::ref(c));

    // f1.get();
    f1.wait();
    std::cout << c << std::endl;
    
    // f2.get();
    f2.wait();
    std::cout << c << std::endl;

    // f3.get();
    f3.wait();
    std::cout << c << std::endl;

    // f4.get();
    f4.wait();
    std::cout << c << std::endl;

    // f6.get();
    f6.wait();
    std::cout << c << std::endl;

    // f7.get();
    f7.wait();
    std::cout << c << std::endl;

    return 0;
}
