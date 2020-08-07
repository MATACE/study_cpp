#ifndef PROTOTYPE_H
#define PROTOTYPE_H

namespace door_adapter {

// Union-Mode-Adapter
class Switch 
{
public:
    Switch() = default;
    virtual ~Switch() = default;
    virtual void Open() = 0;
};

class Man
{
public:
    Man() = default;
    virtual ~Man() = default;
    void TouchSwitch(Switch & switch_) const{
        switch_.Open();
    }
};

class Door
{
public:
    Door() = default;
    virtual ~Door() = default;
    void door_will_open() const {
        std::cout << "Door is opening." << std::endl;
    }
};

class WoodDoor : public Door
{
    using Door::Door;
public:
    WoodDoor() = default;
    virtual ~WoodDoor() = default;
    void door_will_open() const {
        std::cout << "Wood Door is opening." << std::endl;
    }
};

class IronDoor : public Door
{
    using Door::Door;
public:
    IronDoor() = default;
    virtual ~IronDoor() = default;
    void door_will_open() const {
        std::cout << "Iron Door is opening." << std::endl;
    }
};


class SwitchAdapter : public Switch
{
public:
    SwitchAdapter() = default;
    SwitchAdapter(Door &door) :
        door_(door) {}
    virtual ~SwitchAdapter() = default;

    void Open() override {
        door_.door_will_open();
    }

private:
    Door door_;
};

// Object-Mode-Adapter
class WoMan
{
public:
    WoMan() = default;
    virtual ~WoMan() = default;
    virtual void TouchSwitch() = 0;
};

class NewDoor
{
public:
    NewDoor() = default;
    virtual ~NewDoor() = default;
    void Open() const {
        std::cout << "New Door is opening" << std::endl;
    }
};

class DoorSwitchAdapter : public WoMan, private NewDoor
{
public:
    DoorSwitchAdapter() = default;
    virtual ~DoorSwitchAdapter() = default;
    void TouchSwitch() {
        this->Open();
    }
};

}

#endif // PROTOTYPE_H