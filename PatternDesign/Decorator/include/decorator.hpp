#ifndef DECORATIOR_HPP
#define DECORATIOR_HPP

#include <iostream>

using namespace std;

namespace decorator {

class MyLunch {
public:
    MyLunch() = default;
    virtual ~MyLunch() = default;
    virtual void ShowLunch() = 0;
    virtual int ShowPrice() = 0;
};

class LunchPrice : public MyLunch {
public:
    LunchPrice() = default;
    virtual ~LunchPrice() = default;
    void ShowLunch() override {

    }
    int ShowPrice() override {
        return 5;
    }
};

class LunchMenu : public MyLunch {
public:
    LunchMenu() = default;
    LunchMenu (MyLunch& my_lunch)
        : my_lunch_(my_lunch) {}
    virtual ~LunchMenu() = default;

    MyLunch& my_lunch_;
};

class SmallLunch : public LunchMenu {
public:
    SmallLunch() = default;
    SmallLunch(MyLunch& my_lunch)
        : LunchMenu(my_lunch) {}
    virtual ~SmallLunch() = default;
    int ShowPrice() override {
        return my_lunch_.ShowPrice() + 10;
    }
    void ShowLunch() override {
        std::cout << "Rich + Avergage" << std::endl; 
    }
};

class BigLunch : public LunchMenu {
public:
    BigLunch() = default;
    BigLunch(MyLunch& my_lunch)
        : LunchMenu(my_lunch) {}
    virtual ~BigLunch() = default;
    int ShowPrice() override {
        return my_lunch_.ShowPrice() + 20;
    }
    void ShowLunch() override {
        std::cout << "Rich + Avergage + Milk" << std::endl; 
    }
};

}

#endif // DECORATIOR_HPP