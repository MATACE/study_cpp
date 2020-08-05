#ifndef FACADE_HPP
#define FACADE_HPP

#include <iostream>

using namespace std;

namespace facade {

class ComputerHost {
public:
    ComputerHost() = default;
    virtual ~ComputerHost() = default;
    void On() const {
        Run1();
        Run2();
    }

private:
    void Run1() const {
        std::cout << "ComputerHost Run1" << std::endl;
    }

    void Run2() const {
        std::cout << "ComputerHost Run2" << std::endl;
    }

};

class ShowComputer {
public:
    ShowComputer() = default;
    virtual ~ShowComputer() = default;

    void On() const {
        Run1();
        Run2();
    }

private:
    void Run1() const {
        std::cout << "ShowComputer Run1" << std::endl;
    }

    void Run2() const {
        std::cout << "ShowComputer Run2" << std::endl;
    }
};

template<typename T, typename U>
class Power {
public:
    Power();
    Power(T& t1, U& u1)
        : t1_(t1), u1_(u1) {}
    virtual ~Power() = default;

    void TurnOn() const {
        t1_.On();
        u1_.On();
    }

private:
    T& t1_;
    U& u1_;
};

template class Power<ComputerHost, ShowComputer>;

}

#endif // FACADE_HPP