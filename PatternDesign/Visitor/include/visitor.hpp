#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <iostream>

using namespace std;

namespace visitor {

class Monkey;
class Lion;
class Dolphin;

class AnimalOperation {
public:
    AnimalOperation() = default;
    virtual ~AnimalOperation() = default;
    
    virtual void VisitMonkey(Monkey&) = 0;
    virtual void VisitLion(Lion&) = 0;
    virtual void VisitDolphin(Dolphin&) = 0;
};

class Animal {
public:
    Animal() = default;
    virtual ~Animal() = default;
    virtual void Show() = 0;
    virtual void Accpet(AnimalOperation& operation) = 0;
};

class Monkey : public Animal {
public:
    Monkey() = default;
    virtual ~Monkey() = default;
    void Show() override {
        std::cout << "This Monkey" << std::endl;
    }
    void Accpet(AnimalOperation& operation) override {
        operation.VisitMonkey(*this);
    }
};

class Lion : public Animal {
public:
    Lion() = default;
    virtual ~Lion() = default;
    void Show() override {
        std::cout << "This Lion" << std::endl;
    }
    void Accpet(AnimalOperation& operation) override {
        operation.VisitLion(*this);
    }
};


class Dolphin : public Animal {
public:
    Dolphin() = default;
    virtual ~Dolphin() = default;
    void Show() override {
        std::cout << "This Dolphin" << std::endl;
    }
    void Accpet(AnimalOperation& operation) override {
        operation.VisitDolphin(*this);
    }
};

class Speak : public AnimalOperation {
public:
    Speak() = default;
    virtual ~Speak() = default;

    void VisitMonkey(Monkey& monkey) {
        monkey.Show();
    };
    void VisitLion(Lion& lion) {
        lion.Show();
    };
    void VisitDolphin(Dolphin& dolphin) {
        dolphin.Show();
    }
};

}



#endif // VISITOR_HPP