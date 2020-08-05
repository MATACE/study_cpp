#include <iostream>

#include "chain_of_responsibility.hpp"

using namespace std;

using namespace chain_of_responsibility;

int main(int argc, char const *argv[])
{
    Bank bank(100);
    PayPal pay_pal(200);
    BitCoin bit_coin(300);

    bank.SetNext(&pay_pal);
    pay_pal.SetNext(&bit_coin);

    bank.Pay(223);

    return 0;
}
