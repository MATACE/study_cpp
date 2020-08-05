#include <iostream>

#include "flyweight.hpp"

using namespace std;
using namespace flyweight;

int main(int argc, char const *argv[])
{
    WareHouseManage ware_house_manage;

    ware_house_manage.GetWareHouse("mean").Operation();
    ware_house_manage.GetWareHouse("rich").Operation();

    ware_house_manage.GetWareHouse("mean").Operation();
    ware_house_manage.GetWareHouse("rich").Operation();


    return 0;
}
