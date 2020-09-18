#include <iostream>
#include <future>
#include <condition_variable>
#include <mutex>
#include <chrono>

using namespace std;

// int SeeHello(unsigned int time) {
//     // When sleep time, it will wait the function SeeHello end. 
//     std::this_thread::sleep_for(std::chrono::seconds(time));
//     return 1;
// }

// template<typename T>
// void Show(T val) {
//     std::cout << "Get the val: " << val << std::endl;
// }


// int main(int argc, char const *argv[])
// {
//     unsigned int time = 3;
//     std::future<int> f1 = std::async(std::launch::async, SeeHello, time);

//     // Wait for the block timeout.
//     if(f1.wait_for(std::chrono::seconds(2)) == std::future_status::ready) {
//         Show<int>(f1.get());
//     } else {
//         std::cout << "Too late" << std::endl;
//     }

//     while(true) {
//         std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep 2s.
//     }
    
//     return 0;
// }

std::condition_variable cv_;
std::mutex m_;
bool is_time_out_flag_;

void wait_loop()
{
    is_time_out_flag_ = false;
    // Set the out fo time
    unsigned int set_time = 5;
    auto const timeout = std::chrono::steady_clock::now() + std::chrono::seconds(set_time); 
    std::unique_lock<std::mutex> lk(m_);
    // Lock and int the loop to wait the time out
    // If the flag is true then exit
    while(!is_time_out_flag_) {
        if (cv_.wait_until(lk, timeout) == std::cv_status::timeout) {
            break; // return the false flag.
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    std::thread work1([] {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        {
            std::lock_guard<std::mutex> lk(m_);
            is_time_out_flag_ = true;
        }
    });

    work1.detach();

    wait_loop();

    if(!is_time_out_flag_) {
        std::cout << "Is time out." << std::endl;
    } else {
        std::cout << "Not time out." << std::endl;
    }

    return 0;
}

