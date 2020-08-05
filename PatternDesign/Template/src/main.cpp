#include <iostream>

#include "template.hpp"

using namespace std;
using namespace template_api;

int main(int argc, char const *argv[])
{
    CarBuild car_build;
    ShipBuild ship_build;
    
    car_build.build();
    ship_build.build();

    return 0;
}
