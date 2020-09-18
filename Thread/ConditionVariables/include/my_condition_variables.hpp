#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

std::queue<string> data_cache;

class Threads {
public:
    Threads() = default;
    virtual ~Threads() = default;

    void ProducerThread() {
        // Create the producer thread and detach it.
        std::thread producer_thread(&Threads::ProducerTask, this);
        producer_thread.detach();
    }

    void CustomerThread() {
        // Create the customer thread and detach it.
        std::thread customer_thread(&Threads::CustomerTask, this);
        customer_thread.detach();
    }

    void ProducerTask() {
        while (true)
        {   
            HandleProducerTask();

        }
    }
    
    void HandleProducerTask() {
        std::string data = "XY";
        std::this_thread::sleep_for(std::chrono::seconds(5)); // sleep 2s.
        // Producer data.
        std::lock_guard<std::mutex> lk(cv_mutex_);
        data_cache.push(data);
        cv_.notify_one();
    }

    void CustomerTask() {
        while (true)
        {
            // Get the lock status.
            std::unique_lock<std::mutex> lk(cv_mutex_);
            // Wait the condition variable status.
            cv_.wait(lk, [] {
                return (data_cache.size() % 2 == 0 && data_cache.size() != 0) ? true : false;
            });
            // If the wait condition variables is false then the wait
            // will auto free the lock and block the thread.
            // If the wait condition variables is true then the thread
            // can have the lock and it will go the flower logic.
            HandleCustomerTask();
            // The wait will have the lock, so need free it by the handle for to 
            // other thread use.
            lk.unlock();
        }
    }
    
    void HandleCustomerTask() {
        std::cout << "-----------------------" << std::endl;
        while (!data_cache.empty()) {
            std::cout << data_cache.front() << std::endl;
            data_cache.pop();
        }
    }
    
private:
    std::condition_variable cv_;
    mutable std::mutex cv_mutex_;
};