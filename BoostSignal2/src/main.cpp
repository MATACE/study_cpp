#include <unistd.h>

#include <iostream>

#include "door.h"
#include "remote.h"

using namespace std;

int main(int argc, char const *argv[])
{   
    Door door;
    Remote remote;
    
    door.init();
    remote.Init();

    while (1)
    {
        sleep(2);
    }

    return 0;
}
