#include <iostream>

#include "abstract_factory.hpp"

using namespace std;
using namespace abstract_factory;

extern template class FishRodFactory<BigFishRod, BigFish>;
extern template class FishRodFactory<SmallFishRod, SmallFish>;


int main(int argc, char const *argv[])
{
    FishRodFactory<BigFishRod, BigFish> big_fish_rod;
    FishRodFactory<SmallFishRod, SmallFish> small_fish_rod;

    big_fish_rod.StartProduct();
    big_fish_rod.FitFish();
    small_fish_rod.StartProduct();
    small_fish_rod.FitFish();

#if 0
    FishRodFactory *big_fish_rod_factory = new OtherFishRodFactory<BigFishRod, BigFish>();
    {
        FishRod *big_fish_rod = big_fish_rod_factory->CreateProduct();
        big_fish_rod->SetRodFormat();
        Fish *big_fish = big_fish_rod_factory->CreateFitFish();
        big_fish->IsFish();
    }


    FishRodFactory *small_fish_rod_factory = new OtherFishRodFactory<SmallFishRod, SmallFish>();
    {
        FishRod *small_fish_rod = small_fish_rod_factory->CreateProduct();
        small_fish_rod->SetRodFormat();
        Fish *small_fish = small_fish_rod_factory->CreateFitFish();
        small_fish->IsFish();
    }

#endif

    return 0;
}
