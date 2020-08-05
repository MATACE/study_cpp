#include <iostream>
#include "state.hpp"

using namespace std;
using namespace state;

int main(int argc, char const *argv[])
{
    Switch my_switch(make_shared<BigSize>());

    my_switch.ChangeSize();

    my_switch.SetSize(make_shared<SmallSize>());
    
    my_switch.ChangeSize();

    return 0;
}
