#include <iostream>
#include <future>
#include <functional>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

class OrderRelaxed {
public:
    OrderRelaxed() = default;
    virtual ~OrderRelaxed() = default;

    void WriteXThenY() {
        // The order run.
        x.store(true, std::memory_order_relaxed);
        y.store(true, std::memory_order_relaxed);
    }

    void ReadYThenX() {
        // The order run.
        while (!y.load(std::memory_order_seq_cst));
        if (x.load(std::memory_order_seq_cst)) {
            ++z;
        }
        std::cout << "Read Y Then X Function: "<< z.load() << std::endl;
    }
    
    void Run() {
        // Init atomic val be false.
        x = false;
        y = false;

        z = 0;

        std::thread a(&OrderRelaxed::WriteXThenY, this);
        std::thread b(&OrderRelaxed::ReadYThenX, this);

        a.join();
        b.join();

        assert(z.load() != 0);
    }

private:
    std::atomic<bool> x,y;
    std::atomic<int> z;
};