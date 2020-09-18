#include <iostream>
#include <thread>
#include <exception>
#include <atomic>

using namespace std;

int main(int argc, char const *argv[])
{
    // // Init a atomic val
    // std::atomic_flag f = ATOMIC_FLAG_INIT;
    // // Free atomic
    // f.clear(std::memory_order_release);
    // // Get the old atomic
    // bool x = f.test_and_set();

    // // Use atomic<> mode
    // std::atomic<bool> b;
    // // Read operation
    // bool x = b.load(std::memory_order_acquire);
    // b.store(true);
    // // Write operation
    // x = b.exchange(false, std::memory_order_acq_rel);

    // // Can't understand
    // bool expected=false;
    // while(!b.compare_exchange_weak(expected,true) && !expected);

    unsigned short buf1[1];
    unsigned short buf2[1];
    
    buf1[0] = 0x4f56;
    buf2[0] = 20310;

    if (buf1[0] == buf2[0]) {
        std::cout << "OK" << std::endl;
    }

    return 0;
}



