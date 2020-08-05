#include <iostream>

#include "command.hpp"

using namespace command;

int main(int argc, char const *argv[])
{
    Bulb bulb;
    TurnOff turn_off(bulb);
    TurnOn turn_on(bulb);

    Receiver recv;
    recv.Execute(turn_on);
    recv.Execute(turn_off);

    return 0;
}
