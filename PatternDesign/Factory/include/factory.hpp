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

template<typename T>
class FishRodFactory
{
    using product_ptr = T*;
public:
    FishRodFactory() = default;
    virtual ~FishRodFactory() = default;
    
    void StartProduct() {
        auto fish_rod = this->CreateProduct();
        fish_rod->SetRodFormat();
    }

private:
    product_ptr CreateProduct() const{
        return new T();
    }
    FishRodFactory(const FishRodFactory&) = delete;
    FishRodFactory& operator=(const FishRodFactory&) = delete;
};

template class FishRodFactory<BigFishRod>;
template class FishRodFactory<SmallFishRod>;

#if 0
class FishRodFactory
{
public:
    FishRodFactory() = default;
    virtual ~FishRodFactory() = default;
    
    void StartProduct() {
        FishRod *fish_rod = this->CreateProduct();
        fish_rod->SetRodFormat();
    }

    virtual FishRod* CreateProduct() = 0;

private:
    FishRodFactory(const FishRodFactory&) = delete;
    FishRodFactory& operator=(const FishRodFactory&) = delete;
};

template<typename T>
class OtherFishRodFactory : public FishRodFactory
{
public:
    OtherFishRodFactory() = default;
    virtual ~OtherFishRodFactory() = default;

    FishRod* CreateProduct() override {
        return new T();
    }

private:
    OtherFishRodFactory(const OtherFishRodFactory&) = delete;
    OtherFishRodFactory& operator=(const OtherFishRodFactory&) = delete;
};

#endif

}

#endif // FACTORY_H