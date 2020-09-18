#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;


class SyncAcqRel {
public:
    SyncAcqRel() :
        sync1(false),
        sync2(false),
        sync(0) {

        }
    virtual ~SyncAcqRel() = default;

    void Work1() {
        // First run.
        data[0].store(42, std::memory_order_relaxed);
        data[1].store(97, std::memory_order_relaxed);
        data[2].store(17, std::memory_order_relaxed);
        data[3].store(-141, std::memory_order_relaxed);
        data[4].store(2003, std::memory_order_relaxed);
        // Set sync1 by atomic release mode.
        sync1.store(true, std::memory_order_release); 
    }

    void TmpWork1() {
        // First run.
        tmp_data[0].store(42, std::memory_order_relaxed);
        tmp_data[1].store(97, std::memory_order_relaxed);
        tmp_data[2].store(17, std::memory_order_relaxed);
        tmp_data[3].store(-141, std::memory_order_relaxed);
        tmp_data[4].store(2003, std::memory_order_relaxed);
        // Set sync by atomic release mode.
        sync.store(1, std::memory_order_release); 
    }

    void Work2() {
        // Second run.
        // Wait the sync1 to run.
        while (!sync1.load(std::memory_order_acquire));

        // Set sync2 by atomic release mode.
        sync2.store(true, std::memory_order_release); 
    }

    void TmpWork2() {
        // Second run.
        // Wait the sync to run.
        int expected = 1;
        while (!sync.compare_exchange_strong(expected, 2, std::memory_order_acq_rel)) {
            expected = 1;
        }
        
    }

    void Work3() {
        // Wait the sync2 to run.
        while (!sync2.load(std::memory_order_acquire));  

        // Check the run order.
        assert(data[0].load(std::memory_order_relaxed) == 42);
        assert(data[1].load(std::memory_order_relaxed) == 97);
        assert(data[2].load(std::memory_order_relaxed) == 17);
        assert(data[3].load(std::memory_order_relaxed) == -141);
        assert(data[4].load(std::memory_order_relaxed) == 2003);

        std::cout << "Run1 Right Run Logic." << std::endl;
    }

    void TmpWork3() {
        while (sync.load(std::memory_order_acquire) < 2)

        // Check the run order.
        assert(tmp_data[0].load(std::memory_order_relaxed) == 42);
        assert(tmp_data[1].load(std::memory_order_relaxed) == 97);
        assert(tmp_data[2].load(std::memory_order_relaxed) == 17);
        assert(tmp_data[3].load(std::memory_order_relaxed) == -141);
        assert(tmp_data[4].load(std::memory_order_relaxed) == 2003);

        std::cout << "Run2 Right Run Logic." << std::endl;
    }

    void Run1() {
        std::thread a(&SyncAcqRel::Work1, this);
        std::thread b(&SyncAcqRel::Work2, this);
        std::thread c(&SyncAcqRel::Work3, this);
        
        a.join();
        b.join();
        c.join();
    }

    void Run2() {
        std::thread a(&SyncAcqRel::TmpWork1, this);
        std::thread b(&SyncAcqRel::TmpWork2, this);
        std::thread c(&SyncAcqRel::TmpWork3, this);
        
        a.join();
        b.join();
        c.join();
    }

private:
    std::atomic<int> data[5];
    std::atomic<int> tmp_data[5];
    std::atomic<bool> sync1;
    std::atomic<bool> sync2;
    std::atomic<int> sync;
};