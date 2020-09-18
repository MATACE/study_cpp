#include <iostream>
#include <atomic>
#include <assert.h>
#include <thread>

using namespace std;

class AtomicFence {
public:
    AtomicFence() = default;
    virtual ~AtomicFence() = default;

    void WriteXThenY() {
        x.store(true, std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_release);
        y.store(true, std::memory_order_relaxed);
    }

    void ReadYThenX() {
        while(!y.load(std::memory_order_relaxed));
        std::atomic_thread_fence(std::memory_order_acquire);
        if (x.load(std::memory_order_relaxed)) {
            z++;
        }
    }

    void Run() {
        x = false;
        y = false;
        z = 0;
        std::thread a(&AtomicFence::WriteXThenY, this);
        std::thread b(&AtomicFence::ReadYThenX, this);
        a.join();
        b.join();
        assert(z.load()!=0); 

        std::cout << "No Error Run" << std::endl;
    }

private:
    std::atomic<bool> x, y;
    std::atomic<int> z;
};
