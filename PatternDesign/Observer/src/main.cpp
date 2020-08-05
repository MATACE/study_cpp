#include <iostream>

#include "observer.hpp"

using namespace std;
using namespace observer;

int main(int argc, char const *argv[])
{
    ShopCart shop_cart;
    shared_ptr<AppleFruits> apple_fruits = make_shared<AppleFruits>();
    shared_ptr<BananaFruits> banana_fruits = make_shared<BananaFruits>();
    shared_ptr<PeachFruits> peach_fruits = make_shared<PeachFruits>();

    shop_cart.AddCostSub(apple_fruits);
    std::cout << shop_cart.Notify() << std::endl;

    shop_cart.AddCostSub(banana_fruits);
    std::cout << shop_cart.Notify() << std::endl;

    shop_cart.AddCostSub(peach_fruits);
    std::cout << shop_cart.Notify() << std::endl;

    shop_cart.DelCostSub(apple_fruits);
    shop_cart.DelCostSub(banana_fruits);
    shop_cart.DelCostSub(peach_fruits);

    return 0;
}
