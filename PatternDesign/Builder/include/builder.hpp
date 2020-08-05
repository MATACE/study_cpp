#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>

namespace builder_mode {

class FishRod
{
public:
    FishRod() = default;
    virtual ~FishRod() = default;
};

class Builder
{
public:
    Builder() = default;
    virtual ~Builder() = default;

    virtual void ChangeWire() = 0;
    virtual void ChangeColor() = 0;
    virtual void ChangeLength() = 0;
    virtual void ChangeName() = 0;

};

class ConcreteBuilder : public Builder
{
    using Builder::Builder;
public:
    ConcreteBuilder() = default;
    virtual ~ConcreteBuilder() = default;

    void ChangeWire() override {
        std::cout << "Change Wire" << std::endl;
    }

    void ChangeColor() override {
        std::cout << "Change Color" << std::endl;
    }

    void ChangeLength() override {
        std::cout << "Change Length" << std::endl;
    }

    void ChangeName() override {
        std::cout << "Change Name" << std::endl;
    }

    FishRod* GetProduct() const {
        return new FishRod;
    }
private:
    FishRod *fish_rod_ = nullptr;
};

class Director
{
public:
    Director() = default;
    Director(Builder* p_builder) {
        builder_ = p_builder;
    }
    virtual ~Director() = default;
    void construct() {
        builder_->ChangeColor();
        builder_->ChangeName();
        builder_->ChangeWire();
        builder_->ChangeLength();
    }
private:
    Builder *builder_;
};

}

#endif // BUILDER_H