#include <iostream>
#include "Iterator.hpp"

using namespace std;
using namespace iterator_api;

int main(int argc, char const *argv[])
{
    StationList station_list;
    station_list.AddStation(RadioStation(89));
    station_list.AddStation(RadioStation(101));
    station_list.AddStation(RadioStation(102));
    station_list.AddStation(RadioStation(103.2));
    
    for (auto&& station : station_list) {
        std::cout << station.GetFrequency() << std::endl;
    }

    station_list.RemoveStation(RadioStation(89));

    for (auto&& station : station_list) {
        std::cout << station.GetFrequency() << std::endl;
    }

    return 0;
}
