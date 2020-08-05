#include <iostream>

using namespace std;

namespace proxy {

class Door {
public:
    Door() = default;
    virtual ~Door() = default;
    virtual void Open() = 0;
    virtual void Close() = 0;
};

class MyDoor : public Door{
public:
    MyDoor() = default;
    virtual ~MyDoor() = default;
    void Open() override {
        std::cout << "Open My Door" << std::endl;
    }
    void Close() override {
        std::cout << "Close My Door" << std::endl;
    }
};

class Security {
public:
    Security() = default;
    Security(Door& door)
        : door_(door) {}
    virtual ~Security() = default;
    
    void Open(const std::string passworld) const {
        if (Cheack(passworld)) {
            door_.Open();
        } else {
            std::cout << "Passworld is not right" << std::endl;
        }
    }
    void Close() const {
        door_.Close();
    }

private:
    bool Cheack(std::string passworld) const {
        passworld == "123" ? true : false;
    }

    Door& door_;
};

}