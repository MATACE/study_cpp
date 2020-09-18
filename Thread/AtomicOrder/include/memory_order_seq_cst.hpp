#include <iostream>
#include <future>
#include <functional>
#include <atomic>
#include <thread>
#include <assert.h>


using namespace std;

class OrderSeqCst {
public:
    OrderSeqCst() = default;
    virtual ~OrderSeqCst() = default;

    void WriteX() {
        // The order run.
        x.store(true, std::memory_order_seq_cst);
    }

    void WriteY() {
        // The order run.
        y.store(true, std::memory_order_seq_cst);
    }

    void ReadXThenY() {
        // The order run.
        while (!x.load(std::memory_order_seq_cst));
        if (y.load(std::memory_order_seq_cst)) {
            ++z;
        }
        std::cout << "Read X Then Y Function: "<< z.load() << std::endl;
    }

    void ReadYThenX() {
        // The order run.
        while (!y.load(std::memory_order_seq_cst));
        if (y.load(std::memory_order_seq_cst)) {
            ++z;
        }
        std::cout << "Read Y Then X Function: "<< z.load() << std::endl;
    }
    
    void Run() {
        // Init atomic val be false.
        x = false;
        y = false;

        z = 0;

        std::thread a(&OrderSeqCst::WriteX, this);
        std::thread b(&OrderSeqCst::WriteY, this);
        std::thread c(&OrderSeqCst::ReadXThenY, this);
        std::thread d(&OrderSeqCst::ReadYThenX, this);

        a.join();
        b.join();
        c.join();
        d.join();

        assert(z.load() != 0);
    }

private:
    std::atomic<bool> x,y;
    std::atomic<int> z;

};