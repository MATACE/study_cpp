#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

namespace simple_factory {

class Door 
{
public:
    Door() = default;
    virtual ~Door() = default;

    virtual float GetHeight() = 0;
    virtual float GetWidth() = 0;
};

class MyDoor : public Door 
{
public:
    using Door::Door;
    
    MyDoor() = default;
    MyDoor(float height, float width)
        : height_(height), width_(width) { }
    virtual ~MyDoor() = default;

    float GetHeight() override {
        return height_;
    }
    
    float GetWidth() override {
        return width_;
    }
    
private:
    float height_;
    float width_;
};

class DoorFactory 
{
public:
    DoorFactory() = default;
    virtual ~DoorFactory() = default;
    static DoorFactory* GetInstace() {
        return m_instanceSingleton;
    }

    static Door* CreateDoor(float height, float width) {
        return new MyDoor(height, width);
    } 
    
private:
    DoorFactory(const DoorFactory&) = delete;
    DoorFactory& operator=(const DoorFactory&) = delete;
    static DoorFactory* m_instanceSingleton;
};

DoorFactory* DoorFactory::m_instanceSingleton = new DoorFactory;
}

#endif // PRODUCT_H