#include <iostream>
#include <thread>
#include <exception>

#include "promises_future.hpp"

using namespace std::placeholders;

int main(int argc, char const *argv[])
{
    std::promise<int> my_pri;
    std::thread work1([](std::promise<int>& p){
        // Sleep 10s.
        std::this_thread::sleep_for(std::chrono::seconds(2));
        try {
            p.set_value(32);
        } catch(...) {
            // Throw the system error
            p.set_exception(std::current_exception());
            // Throw the custom error
            p.set_exception(std::make_exception_ptr(std::logic_error("The value is less than zero.")));
        }
        
    }, std::ref(my_pri));
    // Need run the thread.
    work1.detach();

    // The share_future can be copy then can pass to other thread and
    // the other can to wait the result to count.
    std::shared_future<int> sf = my_pri.get_future().share();

    std::thread work2([] (std::shared_future<int> f) {
        try {
            // The share_future can by run more times.
            std::cout << "Work2 " << f.get() << std::endl;
        } catch(...) {
            std::cout << "Work2 Wait error" << std::endl;
        }
    }, sf);
    work2.detach();

    std::thread work3([] (std::shared_future<int> f) {
        try {
            // The share_future can by run more times.
            std::cout << "Work3 " << f.get() << std::endl;
        } catch(...) {
            std::cout << "Work3 Wait error" << std::endl;
        }
    }, sf);
    work3.detach();

    //------ future ----------
    // By the future only run one times and only one by other thread run get function.
    std::future<int> my_future = my_pri.get_future();

    // Get the thread return value
    std::cout << "Main get" << my_future.get() << std::endl;


    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

}
