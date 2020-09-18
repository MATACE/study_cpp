#include <iostream>
#include <future>
#include <functional>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

class OrderAcqRel {
public:
    OrderAcqRel() = default;
    virtual ~OrderAcqRel() = default;

    void WriteXThenY() {
        // The order run.
        x.store(true, std::memory_order_release);
        y.store(true, std::memory_order_release);
    }

    void ReadYThenX() {
        // The order run.
        while (!y.load(std::memory_order_acquire));
        if (x.load(std::memory_order_relaxed)) {
            ++z;
        }
        std::cout << "Read Y Then X Function: "<< z.load() << std::endl;
    }
    
    void Run() {
        // Init atomic val be false.
        x = false;
        y = false;

        z = 0;

        std::thread a(&OrderAcqRel::WriteXThenY, this);
        std::thread b(&OrderAcqRel::ReadYThenX, this);

        a.join();
        b.join();

        assert(z.load() != 0);
    }

private:
    std::atomic<bool> x,y;
    std::atomic<int> z;
};