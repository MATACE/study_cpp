#include "door.h"

Door::Door()
{
    val_ = 0;
}

Door::~Door()
{

}

void Door::init()
{
    std::thread run_door(&Door::Run, this);
    run_door.detach();
    return;
}

void Door::Open(int num)
{
    val_ = num;
    cout << "Open " << num << " door." << endl;
    cout << "Door Open thead id " << std::this_thread::get_id() << endl;
}


void Door::Run()
{
    while (1)
    {
        sleep(7);
        cout << "Wait open door." << val_ << endl;
        cout << "Door Run thead id " << std::this_thread::get_id() << endl;
    }
    
}