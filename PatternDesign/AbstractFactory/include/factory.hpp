#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>

namespace factory {

using namespace std;

typedef struct {
    std::string name;
    int len;
} CONFIG;


class FishRod
{
public:
    FishRod() = default;
    virtual ~FishRod() = default;

    virtual bool SetRodFormat() = 0;
};

class SmallFishRod : public FishRod
{
public:
    SmallFishRod() = default;
    virtual ~SmallFishRod() = default;
    using FishRod::FishRod;

    bool SetRodFormat() override {
        cout << "Small Fish Rod" << endl; 
    }
private:
    CONFIG config_;
};

class BigFishRod : public FishRod
{
public:
    BigFishRod() = default;
    virtual ~BigFishRod() = default;
    bool SetRodFormat() override {
        cout << "Big Fish Rod" << endl; 
    }

private:
    CONFIG config_;
};


class Fish
{
public:
    Fish() = default;
    virtual ~Fish() = default;

    virtual bool IsFish() = 0;
};

class BigFish : public Fish
{
    using Fish::Fish;
public:
    BigFish() = default;
    virtual ~BigFish() = default;
    
    bool IsFish() override {
        cout << "Is Big Fish" << endl;
    }
};

class SmallFish : public Fish
{
    using Fish::Fish;
public:
    SmallFish() = default;
    virtual ~SmallFish() = default;

    bool IsFish() override {
        cout << "Is Small Fish" << endl;
    }
};

template<typename T, typename U>
class FishRodFactory
{
    using product_ptr = T*;
    using fish_ptr = U*;
public:
    FishRodFactory() = default;
    virtual ~FishRodFactory() = default;
    
    void StartProduct() {
        auto fish_rod = this->CreateProduct();
        fish_rod->SetRodFormat();
    }

    void FitFish() {
        auto fit_fish = this->CreateFitFish();
        fit_fish->IsFish();
    }

private:
    product_ptr CreateProduct() const {
        return new T();
    }
    fish_ptr CreateFitFish() const {
        return new U();
    }

    FishRodFactory(const FishRodFactory&) = delete;
    FishRodFactory& operator=(const FishRodFactory&) = delete;
};

template class FishRodFactory<BigFishRod, BigFish>;
template class FishRodFactory<SmallFishRod, SmallFish>;

#if 0
class FishRodFactory
{
public:
    FishRodFactory() = default;
    virtual ~FishRodFactory() = default;

    virtual FishRod* CreateProduct() = 0;
    virtual Fish* CreateFitFish() = 0;

private:
    FishRodFactory(const FishRodFactory&) = delete;
    FishRodFactory& operator=(const FishRodFactory&) = delete;
};

template<typename T, typename U>
class OtherFishRodFactory : public FishRodFactory
{
public:
    OtherFishRodFactory() = default;
    virtual ~OtherFishRodFactory() = default;

    FishRod* CreateProduct() override {
        return new T();
    }

    Fish* CreateFitFish() override {
        return new U();
    }

private:
    OtherFishRodFactory(const OtherFishRodFactory&) = delete;
    OtherFishRodFactory& operator=(const OtherFishRodFactory&) = delete;
};

#endif

}

#endif // FACTORY_H