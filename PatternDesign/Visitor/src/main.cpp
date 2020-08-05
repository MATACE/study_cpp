#include <iostream>

#include "visitor.hpp"

using namespace std;
using namespace visitor;

int main(int argc, char const *argv[])
{
    Monkey monkey;
    Lion lion;
    Dolphin dolphin;

    Speak speak;

    monkey.Accpet(speak);
    lion.Accpet(speak);
    dolphin.Accpet(speak);

    return 0;
}
