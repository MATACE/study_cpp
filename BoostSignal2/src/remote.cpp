#include "remote.h"


Remote::Remote()
{
    val_ = 100;
}

Remote::~Remote()
{

}

void Remote::Init()
{
    std::thread run_remote(&Remote::Run, this);
    run_remote.detach();
    return;
}

void Remote::InitRemote()
{
    sig_.connect(Door());
}

void Remote::Run()
{
    InitRemote();
    while (1)
    {
        sleep(5);
        cout << "Remote to open door." << endl;
        KeyOn();
    }
    
}

void Remote::KeyOn()
{
    val_++;
    cout << "Remote thead id " << std::this_thread::get_id() << endl;
    sig_(val_);
    cout << "Remote thead id " << std::this_thread::get_id() << endl;
}