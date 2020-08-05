#ifndef FLYWEIGHT_HPP
#define FLYWEIGHT_HPP

#include <iostream>
#include <map> 
#include <algorithm>

using namespace std;

namespace flyweight {

class WareHouse {
public:
    WareHouse() = default;
    WareHouse(std::string name, unsigned int size = 36)
        : ware_house_name_(name), ware_house_size_(size) {}
    virtual ~WareHouse() = default;
    virtual void Operation() = 0;

    unsigned int ware_house_size_;
    std::string ware_house_name_;
};

class MeanWareHouse : public WareHouse {
public:
    MeanWareHouse() = default;
    MeanWareHouse(std::string name, unsigned int size = 64)
        : WareHouse(name, size) {}
    virtual ~MeanWareHouse() = default;
    void Operation() override {
        std::cout << "Name: " << ware_house_name_ << std::endl;
        std::cout << "Size: " << ware_house_size_ << std::endl;
    }
};

class RichWareHouse : public WareHouse {
public:
    RichWareHouse() = default;
    RichWareHouse(std::string name, unsigned int size = 64)
        : WareHouse(name, size) {}
    virtual ~RichWareHouse() = default;
    void Operation() override {
        std::cout << "Name: " << ware_house_name_ << std::endl;
        std::cout << "Size: " << ware_house_size_ << std::endl;
    }
};

class WareHouseManage {
public:
    WareHouseManage() = default;
    virtual ~WareHouseManage() = default;

    WareHouse& GetWareHouse(std::string ware_house_name) {
        if (WareHouseManageMap.find(ware_house_name) == WareHouseManageMap.end()) {
            if (ware_house_name == "mean") {
                WareHouseManageMap[ware_house_name] = new MeanWareHouse(ware_house_name);
            } else if (ware_house_name == "rich") {
                WareHouseManageMap[ware_house_name] = new RichWareHouse(ware_house_name);
            }
        } 

        return *(WareHouseManageMap[ware_house_name]);

    };

    map<std::string, WareHouse*> WareHouseManageMap;
};

}

#endif // FLYWEIGHT_HPP