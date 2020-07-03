#ifndef DOOR_H
#define DOOR_H

#include <unistd.h>

#include <iostream>
#include <thread>

using namespace std;

class Door
{
public:
    Door();
    int operator()(int x){
        cout << "slot " << x << " called" << endl;
        cout << "Door operator thead id " << std::this_thread::get_id() << endl;
        Open(x);
    }
    virtual ~Door();
    void init();
    void Open(int num);
    void Run();
private:
    int val_;
};

#endif // DOOR_H