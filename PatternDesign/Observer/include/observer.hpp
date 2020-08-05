#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <iostream>
#include <list>
#include <memory>

using namespace std;

namespace observer {

class Fruits {
public:
    Fruits() = default;
    virtual ~Fruits() = default;
    virtual int Cost() = 0;
};

class AppleFruits : public Fruits {
public:
    AppleFruits() = default;
    virtual ~AppleFruits() = default;
    int Cost() override {
        return 5;
    }
};

class BananaFruits : public Fruits {
public:
    BananaFruits() = default;
    virtual ~BananaFruits() = default;
    int Cost() override {
        return 11;
    }
};

class PeachFruits : public Fruits {
public:
    PeachFruits() = default;
    virtual ~PeachFruits() = default;
    int Cost() override {
        return 3;
    }

};

class Sub {
public:
    Sub() = default;
    virtual ~Sub() = default;

    virtual void AddCostSub(const shared_ptr<Fruits>&) = 0;
    virtual void DelCostSub(const shared_ptr<Fruits>&) = 0;
    virtual unsigned int Notify() = 0;
    virtual void SetSub(const shared_ptr<Sub>&) = 0;

    list<shared_ptr<Fruits>> list_;
    shared_ptr<Sub> sub_;
};

class ShopCart : public Sub {
public:
    ShopCart() = default;
    virtual ~ShopCart() = default;
    
    void AddCostSub(const shared_ptr<Fruits>& fruits_sub) override {
        list_.push_back(fruits_sub);
    }

    void DelCostSub(const shared_ptr<Fruits>& fruits_sub) override {
        list_.remove(fruits_sub);
    }

    unsigned int Notify() override {
        unsigned int num = 0;
        for (auto iter = list_.begin(); iter != list_.end(); ++iter) {
            num += (*iter)->Cost();
        }

        return num;
    }

    void SetSub(const shared_ptr<Sub>& sub) override {
        sub_ = sub;
    }

};
 
}

#endif // OBSERVER_HPP