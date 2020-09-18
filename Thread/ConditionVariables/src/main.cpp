#include <iostream>

#include "my_condition_variables.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    
    // Create the producer and customer thread.
    Threads my_threads;

    my_threads.ProducerThread();
    my_threads.CustomerThread();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // sleep 2s.
    }

    return 0;
}
