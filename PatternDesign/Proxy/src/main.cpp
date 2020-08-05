#include <iostream>

#include "proxy.hpp"

using namespace std;
using namespace proxy;

int main(int argc, char const *argv[])
{
    MyDoor my_door;
    Security security(my_door);

    security.Open("123");

    security.Open("1");

    security.Close();

    return 0;
}
