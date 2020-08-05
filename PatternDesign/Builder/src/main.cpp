#include <iostream>

#include "builder.hpp"

using namespace std;
using namespace builder_mode;

int main(int argc, char const *argv[])
{
    Director *b = new Director(new ConcreteBuilder);

    b->construct();

    return 0;
}
