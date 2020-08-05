#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include <iostream>

namespace template_api {

class ProductionLine {
public:
    ProductionLine() = default;
    virtual ~ProductionLine() = default;
    
    virtual void build() {
        build1();
        build1();
    }

    virtual void build1() = 0;
    virtual void build2() = 0;
};

class CarBuild : public ProductionLine {
public:
    CarBuild() = default;
    virtual ~CarBuild() = default;
    
    void build1() override {
        std::cout << "Build Car Stop 1" << std::endl;
    }

    void build2() override {
        std::cout << "Build Cat Stop 2" << std::endl;
    }
};

class ShipBuild : public ProductionLine {
public:
    ShipBuild() = default;
    virtual ~ShipBuild() = default;
    
    void build1() override {
        std::cout << "Build Ship Stop 1" << std::endl;
    }

    void build2() override {
        std::cout << "Build Ship Stop 2" << std::endl;
    }
};

}

#endif // TEMPLATE_HPP