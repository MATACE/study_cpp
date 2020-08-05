#ifndef PROTOTYPE_H
#define PROTOTYPE_H

namespace prototype {

class Prototype {
public:
    Prototype() = default;
    virtual ~Prototype() = default;

    virtual Prototype* Clone() = 0;
};

class ConcretePrototype:public Prototype
{
    using Prototype::Prototype;
public:
    ConcretePrototype() = default;
    ConcretePrototype(const ConcretePrototype&) = default;
    virtual ~ConcretePrototype() = default;

    Prototype* Clone() override {
        return new ConcretePrototype(*this);
    }
};

}

#endif // PROTOTYPE_H