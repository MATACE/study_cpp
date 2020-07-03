#ifndef REMOTE_H
#define REMOTE_H

#include <unistd.h>

#include <iostream>
#include <thread>

#include <boost/signals2.hpp>

#include "door.h"

using namespace std;

class Remote
{
public:
    Remote();
    virtual ~Remote();
    
    void Init();
    void InitRemote();
    void Run();
    void KeyOn();
private:
    boost::signals2::signal <void(int)> sig_;
    int val_;
};

#endif // REMOTE_H