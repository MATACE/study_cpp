#include <iostream>

#include "adapter.hpp"

using namespace std;
using namespace door_adapter;

int main(int argc, char const *argv[])
{
    // Union-Mode-Adapter
#if 0
    
    Door door;
    SwitchAdapter door_switch(door);

    Man man;
    man.TouchSwitch(door_switch);

#endif
    // Object-Mode-Adapter

    DoorSwitchAdapter door_switch_adapter_;
    door_switch_adapter_.TouchSwitch();

    return 0;
}
