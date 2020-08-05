#include <iostream>

#include "factory.hpp"

using namespace std;
using namespace factory;

extern template class FishRodFactory<BigFishRod>;
extern template class FishRodFactory<SmallFishRod>;


int main(int argc, char const *argv[])
{
    FishRodFactory<BigFishRod> big_fish_rod;
    FishRodFactory<SmallFishRod> small_fish_rod;

    big_fish_rod.StartProduct();
    small_fish_rod.StartProduct();

#if 0
    FishRodFactory *big_fish_rod = new OtherFishRodFactory<BigFishRod>();
    FishRodFactory *small_fish_rod = new OtherFishRodFactory<SmallFishRod>();

    big_fish_rod->StartProduct();
    small_fish_rod->StartProduct();
#endif

    return 0;
}
