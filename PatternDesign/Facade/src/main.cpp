#include <iostream>

#include "facade.hpp"

using namespace std;
using namespace facade;

extern template class Power<ComputerHost, ShowComputer>;

int main(int argc, char const *argv[])
{
    ComputerHost computer_host;
    ShowComputer show_computer;
    Power<ComputerHost, ShowComputer> power(computer_host, show_computer);
    power.TurnOn();

    return 0;
}
