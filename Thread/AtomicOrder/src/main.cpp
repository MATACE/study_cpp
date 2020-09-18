#include <iostream>
#include <thread>
#include <exception>
#include <atomic>
#include <vector>
#include <string.h>

using namespace std;

#include "memory_order_seq_cst.hpp"
#include "memory_order_relaxed.hpp"
#include "memory_order_acq_rel.hpp"
#include "memory_order_acq_rel_sync.hpp"
#include "memory_order_consume.hpp"
#include "memory_order_fetch_sub.hpp"

std::vector<int> data;
std::atomic<bool> data_ready(false);

int main(int argc, char const *argv[])
{

    // // Atomic read and write thread.
    // std::thread Read([]{
    //     while(!data_ready.load()) {
    //         std::this_thread::sleep_for(std::chrono::seconds(1));
    //     }
    //     std::cout << "Vector: " << data[0] << std::endl;
    // });

    // Read.detach();

    // std::thread Write([]{
    //     std::this_thread::sleep_for(std::chrono::seconds(2));
    //     data.push_back(42);
    //     data_ready = true;
    // });

    // Write.detach();

    // OrderSeqCst order_seq_cst;
    // order_seq_cst.Run();

    // OrderRelaxed order_relaxed;
    // order_relaxed.Run();

    // OrderAcqRel order_acq_rel;
    // order_acq_rel.Run();
    // SyncAcqRel sync_acq_rel;
    // sync_acq_rel.Run1();
    // sync_acq_rel.Run2();

    // OrderConsume order_consume;
    // order_consume.Run();

    // OrderFetchSub order_fetch_sub;
    // order_fetch_sub.Run();

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // sleep 2s.
    }

    return 0;
}



