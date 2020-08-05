#include <iostream>

#include "simple_factory.hpp"

using namespace std;
using namespace simple_factory;


int main(int argc, char const *argv[])
{
    DoorFactory *door_factory = DoorFactory::GetInstace();
    float height = 1.7;
    float width = 2.1;

    Door* my_door = door_factory->CreateDoor(height, width);

    cout << "Height: " << my_door->GetHeight() << endl;
    cout << "Width: " << my_door->GetWidth() << endl;

    return 0;
}
