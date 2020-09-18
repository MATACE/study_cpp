// #include <unistd.h> 

// #include <iostream>
// #include <thread>
// #include <vector>
// #include <algorithm>
// #include <mutex>

// #include "thread_manager.hpp"

// using namespace std;

// template<typename Iterator, typename T>
// struct accumulate_block
// {
//     void operator()(Iterator first, Iterator last, T& result)
//     {
//         result = std::accumulate(first, last, result);
//     }
// };

// template<typename Iterator, typename T>
// T parallel_accumulate(Iterator first, Iterator last, T init)
// {
//     // std::distance get the stl iter size.
//     unsigned long const length = std::distance(first, last);

//     if(!length) // If length == 0
//     return init;

//     unsigned long const min_per_thread = 25;
//     unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
//     // std::thread::hardware_concurrency() get the thread number
//     unsigned long const hardware_threads = std::thread::hardware_concurrency();
//     unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
//     unsigned long const block_size = length / num_threads; 

//     std::vector<T> results(num_threads);
//     std::vector<std::thread> threads(num_threads - 1); 
//     Iterator block_start = first;
//     for(unsigned long i = 0; i < (num_threads - 1); ++i) {
//         Iterator block_end = block_start;
//         std::advance(block_end,block_size); 
//         threads[i] = std::thread(accumulate_block<Iterator, T>(),\
//             block_start, block_end, std::ref(results[i])); 
//         block_start=block_end;
//     }

//     accumulate_block<Iterator,T>()(block_start, last, results[num_threads - 1]);
//     std::for_each(threads.begin(), threads.end(),
//     std::mem_fn(&std::thread::join));
//     return std::accumulate(results.begin(), results.end(), init);
// }

// void do_work(unsigned id);

// // void f()
// // {
// //     std::vector<std::thread> threads;
// //     for(unsigned i = 0; i < 20; ++i)
// //     {
// //         threads.push_back(std::thread(do_work,i)); // 产生线程
// //     }
// //     // std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join)); // 对每个线程调用join()
// //     std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::detach)); // 对每个线程调用join()
// // }

// class Work 
// {
// public:
//     Work() = default;
//     virtual ~Work() = default;
//     void DoWork(std::string name) {
//         while (1)
//         {
//             sleep(3);
//             std::cout << this_thread::get_id() << std::endl;
//         }  
//     }
    
//     void WorkList() {
//         std::vector<thread> threads;
//         for (unsigned int i = 0; i < 3; ++i) {
//             threads.push_back(std::thread(&Work::DoWork, this, to_string(i)));
//         }
//         for (auto iter = threads.begin(); iter != threads.end(); ++iter) {
//             iter->native_handle();
//         }
//         std::for_each(threads.begin(), threads.end(), mem_fn(&std::thread::detach));
//     }

// };

// int main(int argc, char const *argv[])
// {
    
    
//     return 0;
// }

#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>

using namespace std;

std::list<int> some_list; 
std::mutex some_mutex; 

void add_to_list(int new_value)
{
    {
        // lock
        std::unique_lock<std::mutex> guard(some_mutex); 

        /* unique_lock have more lock operation */

        // guard.lock();
        // guard.unlock();
        // guard.try_lock();

	    some_list.push_back(new_value);
        // lock_guard out of the range will unlock
    }
	std::cout << "Unlock" << std::endl;
}

bool list_contains(int value_to_find)
{
    {
        // lock
        std::unique_lock<std::mutex> guard(some_mutex); 

        /* unique_lock have more lock operation */
        
        // guard.lock();
        // guard.unlock();
        // guard.try_lock();

        return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
        // lock_guard out of the range will unlock
    }
    std::cout << "Unlock" << std::endl;
}

int main(int argc, char const *argv[])
{
    return 0;
}
