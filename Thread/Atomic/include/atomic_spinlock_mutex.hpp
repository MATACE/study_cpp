#include <iostream>
#include <future>
#include <functional>
#include <atomic>

using namespace std;

class SpinlockMutex {
public:
    SpinlockMutex() :
        flag_(ATOMIC_FLAG_INIT) {

        }
    virtual ~SpinlockMutex() = default;
    
    void Lock() {
        while(flag_.test_and_set(std::memory_order_acquire));
    }

    void Unlock() {
        flag_.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag_;
};