#include <iostream>
#include <future>
#include <functional>
#include <atomic>
#include <thread>
#include <assert.h>
#include <vector>

using namespace std;

class OrderFetchSub {
public:
    OrderFetchSub() = default;
    virtual ~OrderFetchSub() = default;
    void WaitForMoreItems() {

    }
    void Process(int i) {

    }
    
    void PopulateQueue() {
        unsigned const number_of_items = 20;
        queue_data.clear();
        for (unsigned i = 0; i < number_of_items; ++i) {
            queue_data.push_back(i);
        }
        // Init store.
        count.store(number_of_items, std::memory_order_release);
    }
    
    void ConsumeQueueItems() {
        while(true) {
            int item_index;
            // 一个“读-改-写”操作
            if((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0) {
                // 等待更多元素
                // WaitForMoreItems(); 
                continue;
            }      
            // 安全读取queue_data
            // Process(queue_data[item_index - 1]); 
        }
    }

    void Run() {
        std::thread a(&OrderFetchSub::PopulateQueue, this);
        std::thread b(&OrderFetchSub::ConsumeQueueItems, this);
        std::thread c(&OrderFetchSub::ConsumeQueueItems, this);

        a.join();
        b.join();
        c.join();

        std::cout << "End Run" << std::endl;
    }

private:
    std::vector<int> queue_data;
    std::atomic<int> count;
};