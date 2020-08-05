#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <iostream>

namespace bridge {

class Day {
public:
    Day() = default;
    virtual ~Day() = default;
    virtual void ShowMyDay() const = 0;
};

class PoorDay : public Day{
public:
    PoorDay() = default;
    virtual ~PoorDay() = default;
    void ShowMyDay() const override {
        Work();
    }
    void Work() const {
        std::cout << "I Need To Work." << std::endl;
    }
};

class RichDay : public Day{
public:
    RichDay() = default;
    virtual ~RichDay() = default;
    void ShowMyDay() const override {
        Shop();
    }
    void Shop() const {
        std::cout << "I Will To Shop" << std::endl;
    }
};

class Human {
public:
    Human() = default;
    Human(Day& day)
        : day_(day) {}
    virtual ~Human() = default;
    virtual void ShowDay() = 0;
protected:
    Day& day_;
};

class Man : public Human {
public:
    Man() = default;
    Man(Day &day) : Human(day) {}
    virtual ~Man() = default;
    void ShowDay() override {
        day_.ShowMyDay();
    } 
};

}

#endif // BRIDGE_HPP