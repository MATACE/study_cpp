#include <iostream>

#include "package_task_future.hpp"

using namespace std::placeholders;

int main(int argc, char const *argv[])
{
    Task my_task;
    std::packaged_task<int(int, int)> task_1(bind(&Task::Add, &my_task, _1, _2));

    // Init the task function to link the package task.
    task_1(2, 3);

    // Init the task function to the future.
    std::future<int> link_task_1 = task_1.get_future();

    std::cout << link_task_1.get() << std::endl;


    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

}
