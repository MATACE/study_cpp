#include <iostream>

#include "prototype.hpp"

using namespace std;
using namespace prototype;

int main(int argc, char const *argv[])
{
    Prototype *p = new ConcretePrototype;
    Prototype *q = p->Clone();

    return 0;
}
