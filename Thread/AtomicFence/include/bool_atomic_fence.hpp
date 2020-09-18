#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

class BoolAtomicFence {
public:
    BoolAtomicFence() = default;
    virtual ~BoolAtomicFence() = default;

    void WriteXThenY() {
        x = true; // 1 在栅栏前存储x
        std::atomic_thread_fence(std::memory_order_release);
        y.store(true, std::memory_order_relaxed); // 2 在栅栏后存储y
    }

    void ReadYThenX() {
        while(!y.load(std::memory_order_relaxed)); // 3 在#2写入前，持续等待
        std::atomic_thread_fence(std::memory_order_acquire);
        if(x) { // 4 这里读取到的值，是#1中写入 
            ++z;
        } 
    }

    void Run() {
        x = false;
        y = false;
        z = 0;
        std::thread a(&BoolAtomicFence::WriteXThenY, this);
        std::thread b(&BoolAtomicFence::ReadYThenX, this);
        a.join();
        b.join();
        assert(z.load() != 0); // 5 断言将不会触发

        std::cout << "No Error Run" << std::endl;
    }

private:
    bool x;
    std::atomic<bool> y;
    std::atomic<int> z;

};