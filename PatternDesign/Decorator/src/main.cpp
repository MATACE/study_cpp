#include <iostream>

#include "decorator.hpp"

using namespace std;
using namespace decorator;

int main(int argc, char const *argv[])
{
    LunchPrice lunch_price;
    SmallLunch small_lunch(lunch_price);
    BigLunch big_lunch(lunch_price);

    small_lunch.ShowLunch();
    std::cout << small_lunch.ShowPrice() << std::endl;

    big_lunch.ShowLunch();
    std::cout << big_lunch.ShowPrice() << std::endl;
    
    return 0;
}
